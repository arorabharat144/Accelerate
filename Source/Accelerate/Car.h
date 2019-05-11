// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "Materials/Material.h"
#include "PrimaryWeapon.h"
#include "Car.generated.h"


class UCurveFloat;
class USuspensionComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class USuspensionComponent;
class UMaterial;


//START RAMMING CODE================================================
UENUM()
enum RammingColor
{
	Blue	UMETA(DisplayName = "Blue"),
	Red		UMETA(DisplayName = "Red")
};
//END RAMMING CODE================================================

UCLASS()
class ACCELERATE_API ACar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACar();

	void Accelerate(float value);
	void BreakAndDrift();
	void TurnOfDrift();
	void Turn(float value);
	void Boost();
	void BoostTrueorFalse();
	void PitchCar(float value);
	void ActivateFlash();
	void ActivateInvencibilityFor(float timeInSeconds);
	void SetIsInvencible(bool invencible) { mIsInvencible = invencible; }

	//============================================================Start Bullet Code(Alejandro)
	UFUNCTION(BlueprintCallable, Category = "CarToWeapon")
	float GetCurrentSpeedOfCar();
	//============================================================End Bullet Code(Alejandro)
	UFUNCTION(BlueprintCallable, Category = "Fog Weapon")
	void SlowCar(bool activate, float mod);

	UFUNCTION(BlueprintCallable, Category = "Phase Weapon")
	void ActivatePhase(float timer);
	UFUNCTION(BlueprintCallable, Category = "Phase Weapon")
	bool GetIsPhasing() const { return mIsPhasing; }
	UFUNCTION(BlueprintCallable, Category = "Phase Weapon")
	void SetIsPhasing(bool isphasing) { mIsPhasing = isphasing; }


	USceneComponent* GetRoot() { return RootComponent; }
	

protected:
	bool mIsInvencible{ false };

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//START RAMMING CODE================================================
	UFUNCTION()
	bool GetCanRam() { return mCanRam; }

	UFUNCTION()
	void SetCanRam(bool canRam) { mCanRam = canRam; }

	//END RAMMING CODE================================================

	UFUNCTION()

	void EnableDamage() { mCanTakeDamage = true; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* RLMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* RRMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* FLMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* FRMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;

	UPROPERTY(Category = "Suspension", EditAnywhere)
	USuspensionComponent* FrontLeft;

	UPROPERTY(Category = "Suspension", EditAnywhere)
	USuspensionComponent* FrontRight;

	UPROPERTY(Category = "Suspension", EditAnywhere)
	USuspensionComponent* RearLeft;

	UPROPERTY(Category = "Suspension", EditAnywhere)
	USuspensionComponent* RearRight;

	UPROPERTY(Category = "PhysicsEnvironment", EditAnywhere)
	float gravity{ 4000.0f };

	UPROPERTY(Category = "Engine", EditAnywhere)
	UCurveFloat* Curve;

	UPROPERTY(Category = "Engine", EditAnywhere)
	UCurveFloat* TurnCurve;

	UPROPERTY(Category = "Flash Effect", EditAnywhere)
	UCurveFloat* flashCurve;

	UPROPERTY(Category = "Flash Effect", EditAnywhere)
	float maxFlashTimeEffect{ 4.0f };

	UPROPERTY(Category = "Engine", EditAnywhere)
	float Throtle{ 0.0f };

	UPROPERTY(Category = "Engine", EditAnywhere)
	float mAcceleration{ 5.0f };

	UPROPERTY(EditAnywhere, Category = "Engine")
	float MaxBackwardsPower{ 4000.0f };

	UPROPERTY(EditAnywhere, Category = "Engine")
	float MaxPower{ 7500.0f };

	UPROPERTY(EditAnywhere, Category = "Engine")
	float BreakForce{ -6000.0f };

	UPROPERTY(EditAnywhere, Category = "Engine")
	float mTurnForce{ 500000.0f };

	UPROPERTY(EditAnywhere, Category = "Engine")
	float mLateralFriction{ 100.0f };

	UPROPERTY(EditAnywhere, Category = "Engine")
	FVector EngineLinearVelocity;

	UPROPERTY(EditAnywhere, Category = "Engine")
	float mCurrentSpeed{ 0.0f };

	UPROPERTY(EditAnywhere, Category = "Engine")
	float mMaxSpeed{ 30000.0f };

	UPROPERTY(EditAnywhere, Category = "Track")
	float TrackFriction{ 0.4f };

	UPROPERTY(EditAnywhere, Category = "Steering")
	FVector mHeading;

	UPROPERTY(EditAnywhere, Category = "Steering")
	float mCurrenSteeringAngle{ 0.0f };

	UPROPERTY(EditAnywhere, Category = "Steering")
	float mMaxSteeringAngle{ 40.0f };

	UPROPERTY(EditAnywhere, Category = "Steering")
	float mAngularVelocity = 120.0f;

	UPROPERTY(EditAnywhere, Category = "Engine")
	float mPitchForce{ 500000.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boost")
	float mBoostCurrent = 69;

	UPROPERTY(EditAnywhere, Category = "Boost")
	float mBoostMax = 100;

	UPROPERTY(EditAnywhere, Category = "Boost")
	float boostGaugeDelay = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Boost")
	float Timer = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Boost")
	float BoostGain = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Boost")
	bool BoostTrue = false;

	UPROPERTY(EditAnywhere, Category = "Boost")
	float ForceOnGround = 200;

	UPROPERTY(EditAnywhere, Category = "Boost")
	float ForceInAir = 25;

	UPROPERTY(EditAnywhere, Category = "Boost")
	float mMaxBoostSpeed = 40000;

	UPROPERTY(EditAnywhere, Category = "Boost")
	float mBoostUsed = 0.5f;

	UPROPERTY(EditAnywhere, Category = "CameraProperties")
	float lagStep = 2.0f;

	UPROPERTY(EditAnywhere, Category = "CameraProperties")
	float lagDistanceModifier = 100.0f;

	UPROPERTY(EditAnywhere, Category = "CameraProperties")
	float lagMaxDistance = 500.0f;

	UPROPERTY(EditAnywhere, Category = "CameraProperties")
	float lagMinDistance = 50.0f;

	UPROPERTY(EditAnywhere, Category = "CameraProperties")
	float lagCurrentDistance = 100.0f;
		
	UPROPERTY(EditAnywhere, Category = "Car Stability")
	float Stability = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Car Stability")
	float StabilizingSpeed = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Car Stability")
	float rollBackForce = 15000.0f;

	UPROPERTY(EditAnywhere, Category = "Phase Effect")
	float phaseTimer = 3.0f;



private:

	bool mCanRam;
	bool mIsCameraLagging;

	float mFlashTimer;
	float mTempMaxSpeed;

	bool mIsPhasing{ false };

	
	float mBlinkingTimer{ 0.0f };
	float mMaxBlinkingTimer{ 0.05f };
	bool mBlinkOn{ false };

	bool mMeshIsOverlaping{ false };


	FString displayText;
	bool mCanTakeDamage{ true };

	float mCurrentLateralFriction{ 100.0f };
	void BalanceCar();
	void ApplyGravity();
	void SolveSuspension();
	FVector CalculateSuspensionForce(USuspensionComponent* suspension, FHitResult hit);
	bool OnGround();
	void LagOnBoost();
	void ActivateRearCamera();
	void ActivateRotationLag();
	void TestJump();
	bool IsUpsideDown();
	void ApplyCounterTorque();
	void PhaseMaterialEffect(bool active);
	void PhasePhysicsEffect(bool active);
	void UpdateFlashEffect();
	void BlinkingEffect();
};