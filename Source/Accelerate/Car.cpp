// Fill out your copyright notice in the Description page of Project Settings.

#include "Car.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "Engine/Classes/Components/InputComponent.h"
#include "Engine/Classes/Curves/CurveFloat.h"
#include "Engine/Classes/Materials/Material.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/SphereComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Core/Public/Misc/OutputDeviceNull.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "FlameThrower.h"
#include "SuspensionComponent.h"



// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//START RAMMING CODE========================================================================
	mCanRam = true;
	//END RAMMING CODE========================================================================

	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	RLMesh = CreateDefaultSubobject<UStaticMeshComponent>("RearLeftWheelMesh");
	RLMesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	RRMesh = CreateDefaultSubobject<UStaticMeshComponent>("RearRightWheelMesh");
	RRMesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	FLMesh = CreateDefaultSubobject<UStaticMeshComponent>("FrontLeftWheelMesh");
	FLMesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	FRMesh = CreateDefaultSubobject<UStaticMeshComponent>("FrontRightWheelMesh");
	FRMesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	FrontLeft = CreateDefaultSubobject<USuspensionComponent>("Front_Left");
	FrontRight = CreateDefaultSubobject<USuspensionComponent>("Front_Right");
	RearLeft = CreateDefaultSubobject<USuspensionComponent>("Rear_Left");
	RearRight = CreateDefaultSubobject<USuspensionComponent>("Rear_Right");

	RootComponent = Mesh;

	FrontLeft->SetupAttachment(Mesh);
	FrontRight->SetupAttachment(Mesh);
	RearLeft->SetupAttachment(Mesh);
	RearRight->SetupAttachment(Mesh);

	RLMesh->SetupAttachment(RearLeft);
	RRMesh->SetupAttachment(RearRight);
	FLMesh->SetupAttachment(FrontLeft);
	FRMesh->SetupAttachment(FrontRight);

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	mIsCameraLagging = true;

	mTempMaxSpeed = mMaxSpeed;
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	mFlashTimer = 4.0f;

	mTempMaxSpeed = mMaxSpeed;
	
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ApplyGravity();
	SolveSuspension();

	mCurrentLateralFriction += 10.0f * GetWorld()->GetDeltaSeconds();
	if (mCurrentLateralFriction > mLateralFriction)
	{
		mCurrentLateralFriction = mLateralFriction;
	}
	// Boost =========================================================
	FString str = FString::SanitizeFloat(mBoostCurrent);
	//GEngine->AddOnScreenDebugMessage(-1, -1.0f, FColor::Turquoise, str);
	Timer += 0.1f;
	if (mCurrentSpeed <= mMaxBoostSpeed)
	{
		
		if (BoostTrue && mBoostCurrent > 0)
		{

			Boost();
			mBoostCurrent -= mBoostUsed;
		}
	}

	if (Timer >= boostGaugeDelay && mBoostCurrent <= (mBoostMax - 1))
	{

		mBoostCurrent += BoostGain;
		Timer = 0.0f;
	}

	LagOnBoost();
	BalanceCar();
	ApplyCounterTorque();
	
	UpdateFlashEffect();
	BlinkingEffect();
	
}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("HandBrakes", EInputEvent::IE_Repeat, this, &ACar::BreakAndDrift);
	//InputComponent->BindAction("HandBrakes", IE_Released, this, &ACar::TurnOfDrift);
	InputComponent->BindAxis("MoveForward", this, &ACar::Accelerate);
	InputComponent->BindAxis("MoveRight", this, &ACar::Turn);
	InputComponent->BindAxis("PitchCar", this, &ACar::PitchCar);

	
	InputComponent->BindAction("BoostTrueorFalse", EInputEvent::IE_Pressed, this, &ACar::BoostTrueorFalse);
	InputComponent->BindAction("BoostTrueorFalse", EInputEvent::IE_Released, this, &ACar::BoostTrueorFalse);
	InputComponent->BindAction("ActivateRearCamera", EInputEvent::IE_Pressed, this, &ACar::ActivateRearCamera);
	InputComponent->BindAction("ActivateRearCamera", EInputEvent::IE_Released, this, &ACar::ActivateRearCamera);
	InputComponent->BindAction("JumpTest", EInputEvent::IE_Released, this, &ACar::TestJump);
}



void ACar::SolveSuspension()
{
	FRotator actorRotation = GetActorRotation();
	auto quat = actorRotation.Quaternion();

	FHitResult hitRearLeft;
	FHitResult hitRearRight;
	FHitResult hitFrontLeft;
	FHitResult hitFrontRight;

	bool isHit1 = RearLeft->CastRay(hitRearLeft);
	bool isHit2 = RearRight->CastRay(hitRearRight);
	bool isHit3 = FrontLeft->CastRay(hitFrontLeft);
	bool isHit4 = FrontRight->CastRay(hitFrontRight);

	FVector TotalForceRL = FVector::ZeroVector;
	FVector TotalForceRR = FVector::ZeroVector;
	FVector TotalForceFL = FVector::ZeroVector;
	FVector TotalForceFR = FVector::ZeroVector;

	if (isHit1)
	{
		TotalForceRL = CalculateSuspensionForce(RearLeft, hitRearLeft);
	}
	if (isHit2)
	{
		TotalForceRR = CalculateSuspensionForce(RearRight, hitRearRight);
	}
	if (isHit3)
	{
		TotalForceFL = CalculateSuspensionForce(FrontLeft, hitFrontLeft);
	}
	if (isHit4)
	{
		TotalForceFR = CalculateSuspensionForce(FrontRight, hitFrontRight);
	}

	Mesh->AddForceAtLocation(TotalForceRL, RearLeft->GetComponentLocation());
	Mesh->AddForceAtLocation(TotalForceRR, RearRight->GetComponentLocation());
	Mesh->AddForceAtLocation(TotalForceFL, FrontLeft->GetComponentLocation());
	Mesh->AddForceAtLocation(TotalForceFR, FrontRight->GetComponentLocation());

}


FVector ACar::CalculateSuspensionForce(USuspensionComponent* suspension, FHitResult hit)
{
	//DONE
	FVector suspDirectionForce = UKismetMathLibrary::Normal(hit.TraceStart - hit.TraceEnd);

	FVector vel = Mesh->GetPhysicsLinearVelocityAtPoint(suspension->GetComponentLocation());
	float ratio = 1.0f - hit.Distance / suspension->SuspensionLength;

	FVector force = (hit.ImpactNormal * suspension->KSuspension * (ratio)) -
		(suspension->KDamp * hit.ImpactNormal * UKismetMathLibrary::Dot_VectorVector(suspDirectionForce, vel));


	return force;
}

void ACar::Accelerate(float value)
{

	if (value > 0.0f || value < 0.0f)
	{
		//Changing direction
		if ((Throtle > 0.0f && value < 0.0f) || (Throtle < 0.0f && value > 0.0f))
		{
			Throtle = 0.0f;
		}
		Throtle += value * mAcceleration * GetWorld()->GetDeltaSeconds();

		if (Throtle > MaxPower)
		{
			Throtle = MaxPower;
		}
		else if (Throtle < (-MaxBackwardsPower))
		{
			Throtle = -MaxBackwardsPower;
		}
	}
	else
	{
		if (Throtle > 0.0f)
		{
			Throtle -= mAcceleration * GetWorld()->GetDeltaSeconds();
			if (Throtle < 0.0f)
			{
				Throtle = 0.0f;
			}
		}
		else if (Throtle < 0.0f)
		{
			Throtle += mAcceleration * GetWorld()->GetDeltaSeconds();
			if (Throtle > 0.0f)
			{
				Throtle = 0.0f;
			}
		}

	}

	if (OnGround())
	{
		FVector EnginePower = FVector::ZeroVector;
		EnginePower = mHeading * Curve->GetFloatValue(Throtle) * value;
		Mesh->AddForce(EnginePower);


		//TrackFriction
		float bForceScalar = UKismetMathLibrary::Dot_VectorVector(Mesh->GetComponentVelocity(), UKismetMathLibrary::Normal(Mesh->GetComponentVelocity()));
		FVector bForce = bForceScalar * TrackFriction * (-UKismetMathLibrary::Normal(Mesh->GetComponentVelocity()));
		Mesh->AddForce(bForce);

		FVector velocity = GetVelocity();
		FVector velocityXY = FVector(velocity.X, velocity.Y, 0.0f);
		mCurrentSpeed = UKismetMathLibrary::VSize(velocityXY);

		FVector ClampedVector = UKismetMathLibrary::ClampVectorSize(velocityXY, 0.0f, mMaxSpeed);

		FVector newVelocity = FVector(ClampedVector.X, ClampedVector.Y, velocity.Z);

		if (mCurrentSpeed > mMaxSpeed)
		{
			Mesh->SetPhysicsLinearVelocity(newVelocity);
		}
	}
}
// BOOST ===========================================================

void ACar::Boost()
{
	FVector Force_1 = FVector::ForwardVector;
	Force_1.X = 20.0f;
	FName Boost1 = "Boost";
	FVector Force_2 = FVector::ForwardVector;
	FVector Force_3 = FVector::ForwardVector;

	if (OnGround())
	{
		Force_2.X = -286.0f;
		Force_2.Z = -40.0f;
		Force_2.Y = 0.0f;

		Force_3.X = -286.0f;
		Force_3.Z = 40.0f;
		Force_3.Y = 0.0f;

		Mesh->AddForceAtLocationLocal(Force_1 * ForceOnGround, Force_2, Boost1);
		Mesh->AddForceAtLocationLocal(Force_1 * ForceOnGround, Force_3, Boost1);
	}

	//In Air
	if (!OnGround())
	{
		Force_2.X = -286.0f;
		Force_2.Z = -40.0f;
		Force_2.Y = 0.0f;

		Force_3.X = -286.0f;
		Force_3.Z = 40.0f;
		Force_3.Y = 0.0f;

		Mesh->AddForceAtLocationLocal(Force_1 * ForceInAir, Force_2, Boost1);
		Mesh->AddForceAtLocationLocal(Force_1 * ForceInAir, Force_3, Boost1);
	}
}

void ACar::BoostTrueorFalse()
{
	if (!BoostTrue && mBoostCurrent > 0)
	{
		BoostTrue = true;
	}
	else {
		BoostTrue = false;
	}
}


//Start Bullet Code(Alejandro)==================================
float ACar::GetCurrentSpeedOfCar()
{
	return  mCurrentSpeed;
}
	
//End Bullet Code(Alejandro)==================================

void ACar::BalanceCar()
{
		FVector currentAngularVelocity = Mesh->GetPhysicsAngularVelocityInDegrees();
		float angVelMagnitude = UKismetMathLibrary::VSize(currentAngularVelocity);
		float stabilityFactor = angVelMagnitude * Stability;
		if (StabilizingSpeed == 0.0f)
		{
			StabilizingSpeed = 0.1f;
		}
		float stabilityAngle = stabilityFactor / StabilizingSpeed;

		FRotator currentRotation = UKismetMathLibrary::RotatorFromAxisAndAngle(currentAngularVelocity, stabilityAngle);

		FVector currentRightVector = currentRotation.RotateVector(GetActorRightVector());
		FVector currentForwardVector = currentRotation.RotateVector(GetActorForwardVector());

		FRotator zeroRotation = FRotator(0.0f, 0.0f, 0.0f);
		FVector worldRightVector = UKismetMathLibrary::GetRightVector(zeroRotation);
		FVector worldForwardVector = UKismetMathLibrary::GetForwardVector(zeroRotation);

		FVector counterPitchTorque = (currentRightVector * worldRightVector) * (StabilizingSpeed*StabilizingSpeed);
		FVector counterRollTorque = (currentForwardVector * worldForwardVector) * (StabilizingSpeed*StabilizingSpeed);

		Mesh->AddTorqueInRadians(counterPitchTorque);
		Mesh->AddTorqueInRadians(counterRollTorque);
}

void ACar::Turn(float value)
{
	FVector torqueForce = FVector::UpVector * mTurnForce * value * TurnCurve->GetFloatValue(UKismetMathLibrary::Abs(mCurrentSpeed)/mMaxSpeed);

	if (UKismetMathLibrary::Dot_VectorVector(Mesh->GetComponentVelocity(), GetActorForwardVector()) < 0.0f)
	{
		//Backwards
		Mesh->AddTorqueInRadians(-torqueForce);
	}
	else
	{
		Mesh->AddTorqueInRadians(torqueForce);
	}


	mHeading = GetActorForwardVector();
	
	FVector actorVelocity = Mesh->GetComponentVelocity();

	////Regulating Drift
	FVector actorRight = GetActorRightVector();
	float sidewayVelocity = UKismetMathLibrary::Dot_VectorVector(actorVelocity, actorRight);

	float invertedSideway = sidewayVelocity * (-1.0f);

	FVector DriftResistance = actorRight * (invertedSideway * mCurrentLateralFriction);

	Mesh->AddForce(DriftResistance);
}


void ACar::BreakAndDrift()
{
	if (OnGround())
	{
		mCurrentLateralFriction = mLateralFriction * 0.0f;
	}
}

void ACar::TurnOfDrift()
{
	if (OnGround())
	{
		mCurrentLateralFriction = mLateralFriction;
	}
}


bool ACar::OnGround()
{
	uint32_t counter = 4;

	FHitResult hitRearLeft;
	FHitResult hitRearRight;
	FHitResult hitFrontLeft;
	FHitResult hitFrontRight;

	bool isHit1 = RearLeft->CastRay(hitRearLeft);
	bool isHit2 = RearRight->CastRay(hitRearRight);
	bool isHit3 = FrontLeft->CastRay(hitFrontLeft);
	bool isHit4 = FrontRight->CastRay(hitFrontRight);

	if (!isHit1)
	{
		counter--;
	}
	if (!isHit2)
	{
		counter--;
	}
	if (!isHit3)
	{
		counter--;
	}
	if (!isHit4)
	{
		counter--;
	}

	//Just consider the car on ground if more then 2 wheels are touching the ground
	return counter > 2;

}

void ACar::ApplyGravity()
{
	FRotator zeroRotation = FRotator(0.0f, 0.0f, 0.0f);
	FVector worldUpVector = UKismetMathLibrary::GetUpVector(zeroRotation);

	FVector GravityForce = worldUpVector * (-gravity)* Mesh->GetMass();
	Mesh->AddForce(GravityForce);
}

void ACar::PitchCar(float value)
{
	if (!OnGround())
	{
		Mesh->AddTorqueInRadians(Mesh->GetRightVector() * mPitchForce * value);
	}
}

void ACar::LagOnBoost()
{
	if (BoostTrue)
	{
		lagCurrentDistance += lagDistanceModifier * GetWorld()->GetDeltaSeconds();
		if (lagCurrentDistance > lagMaxDistance)
		{
			lagCurrentDistance = lagMaxDistance;
		}

		SpringArm->CameraLagMaxDistance = lagCurrentDistance;
		SpringArm->CameraLagMaxTimeStep = lagStep;
	}
	else
	{
		lagCurrentDistance -= lagDistanceModifier * GetWorld()->GetDeltaSeconds();
		if (lagCurrentDistance < lagMinDistance)
		{
			lagCurrentDistance = lagMinDistance;
		}

		SpringArm->CameraLagMaxDistance = lagCurrentDistance;
		SpringArm->CameraLagMaxTimeStep = lagStep;
	}
}


void ACar::ActivateRearCamera()
{
	const FRotator standardRotation = FRotator(-10.0f, 0.0f, 0.0f);
	if (mIsCameraLagging)
	{
		const FRotator newRotation = FRotator(-10.0f, 180.0f, 0.0f);
		SpringArm->bEnableCameraRotationLag = false;
		SpringArm->SetRelativeRotation(newRotation.Quaternion());
		mIsCameraLagging = false;
	}
	else
	{
		SpringArm->SetRelativeRotation(standardRotation.Quaternion());
		mIsCameraLagging = true;
		FTimerHandle timerHandle;
		GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &ACar::ActivateRotationLag, 0.1f, false);
	}

	float CameraDir = UKismetMathLibrary::Dot_VectorVector(SpringArm->GetForwardVector(), Mesh->GetForwardVector());

	
	
}

void ACar::ActivateRotationLag()
{
	SpringArm->bEnableCameraRotationLag = true;
}

void ACar::TestJump()
{
	//float impulseForce = 3000.0f;
	//FVector impulseAxis = Mesh->GetUpVector();
	//Mesh->AddImpulse(impulseAxis*impulseForce);
	//flashTimer = 0.0f;
	//ActivatePhase(3.0f);
	//SlowCar(0.3f);
	ActivateInvencibilityFor(3.0f);
	
}

bool ACar::IsUpsideDown()
{
	if (!OnGround())
	{
		FRotator zeroRotation = FRotator(0.0f, 0.0f, 0.0f);;
		FVector worldUpVector = UKismetMathLibrary::GetUpVector(zeroRotation);

		FVector meshLocalUp = Mesh->GetUpVector();
		if (UKismetMathLibrary::Dot_VectorVector(meshLocalUp, worldUpVector) <= 0)
		{
			return true;
		}

	}
	return false;
}

void ACar::ApplyCounterTorque()
{
	if (IsUpsideDown())
	{
  		FVector forward = Mesh->GetForwardVector();
		Mesh->AddTorqueInRadians(forward * rollBackForce);
	}
}

void ACar::UpdateFlashEffect()
{
	FPostProcessSettings fPostProcess;
	float flashIntensity = flashCurve->GetFloatValue(mFlashTimer);
	fPostProcess.BloomIntensity = flashIntensity;
	fPostProcess.bOverride_BloomIntensity = true;

	Camera->PostProcessSettings = fPostProcess;
	mFlashTimer += GetWorld()->GetDeltaSeconds();
	
	if (mFlashTimer >= maxFlashTimeEffect)
	{
		mFlashTimer = maxFlashTimeEffect;
	}
}

void ACar::BlinkingEffect()
{
	if (mIsInvencible)
	{
		mBlinkingTimer += GetWorld()->GetDeltaSeconds();
		if (mBlinkingTimer >= mMaxBlinkingTimer)
		{
			mBlinkingTimer = 0.0f;
			if (mBlinkOn == true)
			{
				mBlinkOn = false;
				PhaseMaterialEffect(false);
			}
			else
			{
				mBlinkOn = true;
				PhaseMaterialEffect(true);
			}
		}
	}
	else
	{
		mBlinkingTimer = 0.0f;
	}
}

void ACar::ActivateFlash()
{
	mFlashTimer = 0.0f;
}

void ACar::ActivateInvencibilityFor(float timeInSeconds)
{
	mIsInvencible = true;
	FTimerDelegate TimerDelInvencibleEffect;
	FTimerHandle TimerHandleInvencibleEffect;

	TimerDelInvencibleEffect.BindLambda([&]()
	{
		SetIsInvencible(false);
		PhaseMaterialEffect(false);
	});

	GetWorld()->GetTimerManager().SetTimer(TimerHandleInvencibleEffect, TimerDelInvencibleEffect, timeInSeconds, false);

}

void ACar::ActivatePhase(float timer)
{
	if (mIsPhasing == false)
	{
		FTimerDelegate TimerDelMaterialEffect;
		FTimerDelegate TimerDelPhysicsEffect;
		FTimerHandle TimerHandleMaterialEffect;
		FTimerHandle TimerHandlePhysicsEffect;

		mIsPhasing = true;

		PhaseMaterialEffect(true);
		PhasePhysicsEffect(true);

		TimerDelMaterialEffect.BindLambda([&]()
		{
			PhaseMaterialEffect(false);
			SetIsPhasing(false);
		});

		TimerDelPhysicsEffect.BindLambda([&]()
		{
			PhasePhysicsEffect(false);
			SetIsPhasing(false);
		});
	
		GetWorld()->GetTimerManager().SetTimer(TimerHandleMaterialEffect, TimerDelMaterialEffect, timer, false);
		GetWorld()->GetTimerManager().SetTimer(TimerHandlePhysicsEffect, TimerDelPhysicsEffect, timer, false);
	}
}

void ACar::PhaseMaterialEffect(bool active)
{
	FOutputDeviceNull ar;
	const FString command = FString::Printf(TEXT("ApplyPhaseMaterial %d"), active);
	CallFunctionByNameWithArguments(*command, ar, NULL, true);
}

void ACar::SlowCar(bool activate, float mod)
{
	if (activate)
	{
		mMaxSpeed *= mod;
	}
	else
	{
		mMaxSpeed = mTempMaxSpeed;
	}
}

void ACar::PhasePhysicsEffect(bool active)
{
	if (active == true)
	{
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
	}
	else
	{
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);
	}
}
