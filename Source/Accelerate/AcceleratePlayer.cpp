// Fill out your copyright notice in the Description page of Project Settings.

#include "AcceleratePlayer.h"
#include "Hook.h"
#include "EMP.h"
#include "SecondaryWeapon.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Components/BoxComponent.h"
#include "Engine/Classes/Components/InputComponent.h"
#include "Engine/Classes/Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DomeShield.h"
#include "HomingWeapon.h"
#include "LaserBlaster.h"
#include "FlameThrower.h"
#include "Drain.h"
#include "Mine.h"
#include "GameManager.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"


DEFINE_LOG_CATEGORY(LogAcceleratePlayer);

AAcceleratePlayer::AAcceleratePlayer()
	: Health(100.0f)
	, Boost(100.0f)
	, MaxHealth(100.0f)
	, MaxBoost(100.0f)
	, mPrimaryWeapon(nullptr)
	, mSecondaryWeapon(nullptr)
{
	rammingCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RammingCollider"));
	rammingCollision->SetSimulatePhysics(false);
	rammingCollision->SetNotifyRigidBodyCollision(true);
	rammingCollision->BodyInstance.SetCollisionProfileName(TEXT("OverlapAll"));

	mBaseWeaponLoc = CreateDefaultSubobject<USceneComponent>(TEXT("BaseWeaponLoc"));
}

// Called to bind functionality to input
void AAcceleratePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("FirePrimaryWeapon", this, &AAcceleratePlayer::FirePrimaryWeapon);
	InputComponent->BindAction("FireSecondaryWeapon", EInputEvent::IE_Pressed, this, &AAcceleratePlayer::FireSecondaryWeapon);
	InputComponent->BindAction("Respawn", EInputEvent::IE_Pressed, this, &AAcceleratePlayer::Respawn);
	InputComponent->BindAction("PickupWeaponTest", EInputEvent::IE_Pressed, this, &AAcceleratePlayer::CreateWeaponPickupTest);
}

void AAcceleratePlayer::BeginPlay()
{
	Super::BeginPlay();

	rammingCollision->SetEnableGravity(false);
	rammingCollision->bHiddenInGame = true;
	rammingCollision->OnComponentBeginOverlap.AddDynamic(this, &AAcceleratePlayer::OnOverlapBegin);
}

void AAcceleratePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!mInit)
	{
		SetPlayerFOV();
		mInit = true;
	}

	FTransform rammingCollisionTransform = GetActorTransform();
	FVector rammingCollisionLocation = rammingCollisionTransform.GetLocation();
	rammingCollisionLocation.Z += 30.0f;
	FVector carFowardDirection = GetActorForwardVector();
	carFowardDirection.Normalize();
	rammingCollisionLocation += carFowardDirection * 50.0f;
	rammingCollisionTransform.SetLocation(rammingCollisionLocation);
	rammingCollisionTransform.SetScale3D(FVector(8.0f, 3.0f, 2.0f));
	rammingCollision->SetWorldTransform(rammingCollisionTransform);
}

void AAcceleratePlayer::ReceiveDamage(float damage)
{
	if (!isShieldActive && !mIsInvencible)
	{
		Health -= damage;
		if (Health < 0.0f)
		{
			Health = 0.0f;
		}
	}
}

void AAcceleratePlayer::ReduceBoost(float boost)
{
	Boost -= boost;
	if (Boost < 0.0f)
	{
		Boost = 0.0f;
	}
}

void AAcceleratePlayer::IncreaseHealth(float health)
{
	Health += health;
	if (Health > MaxHealth)
	{
		Health = MaxHealth;
	}
}

void AAcceleratePlayer::IncreaseBoost(float boost)
{
	Boost += boost;
	if (Boost > MaxBoost)
	{
		Boost = MaxBoost;
	}
}

void AAcceleratePlayer::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AAcceleratePlayer::StaticClass()) && OtherActor != this)
	{
		AAcceleratePlayer* otherCar = (AAcceleratePlayer*)OtherActor;
		if (GetCanRam())
		{
			FVector player1Foward, player2Forward;
			player1Foward = GetActorForwardVector();
			player2Forward = OtherActor->GetActorForwardVector();
			player1Foward.Normalize();
			player2Forward.Normalize();
			FVector aD = (player1Foward + player2Forward) / 2.0f;
			aD *= 100.0f;
			FVector tempLocation = GetActorLocation();
			//Calculate Distance of each car to the foward direction
			float thisCarsDistance = abs(FMath::Sqrt(FMath::Square(aD.X - tempLocation.X) +
				FMath::Square(aD.Y - tempLocation.Y) + FMath::Square(aD.Z - tempLocation.Z)));

			tempLocation = OtherActor->GetActorLocation();
			float otherCarsDistance = abs(FMath::Sqrt(FMath::Square(aD.X - tempLocation.X) +
				FMath::Square(aD.Y - tempLocation.Y) + FMath::Square(aD.Z - tempLocation.Z)));

			if (thisCarsDistance > otherCarsDistance)
			{
				//This car does damage and takes boost
				IncreaseBoost(rammingBoostReward);
			}
			else if(!GetIsPhasing())
			{
				//car takes damage and other car gets boost
				float damage = (abs(otherCar->GetCurrentSpeedOfCar() - mCurrentSpeed) / mMaxSpeed) * rammingHealthMaxDamage;
				ReceiveDamage(damage);
			}

			SetCanRam(false);

			FTimerDelegate SetRamDelegate = FTimerDelegate::CreateUObject(this, &AAcceleratePlayer::SetCanRam, true);
			FTimerHandle TimerHandle;

			GetWorldTimerManager().SetTimer(TimerHandle, SetRamDelegate, 1.0f, false, rammingCooldown);
		}
	}
}

void AAcceleratePlayer::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AAcceleratePlayer::FirePrimaryWeapon(float value)
{
	if (mPrimaryWeapon && canUseWeapons)
	{
		mPrimaryWeapon->Fire(value);
	}
}

void AAcceleratePlayer::FireSecondaryWeapon()
{
	if (mSecondaryWeapon && canUseWeapons)
	{
		mSecondaryWeapon->Fire();
	}
}

void AAcceleratePlayer::CreatePrimaryOffensiveWeapon(EPrimaryOffensiveWeaponTypes weaponType)
{
	FActorSpawnParameters params;
	params.Owner = this;

	switch (weaponType)
	{
		case EPrimaryOffensiveWeaponTypes::LaserBlaster:
		{
			mPrimaryWeapon = GetWorld()->SpawnActor<ALaserBlaster>(laserBlasterRef->GetAuthoritativeClass(), params);
			break;
		}
		case EPrimaryOffensiveWeaponTypes::Flamethrower:
		{
			mPrimaryWeapon = GetWorld()->SpawnActor<AFlameThrower>(flameThrowerRef->GetAuthoritativeClass(), params);
			break;
		}
		case EPrimaryOffensiveWeaponTypes::Railgun:
		{
			mPrimaryWeapon = GetWorld()->SpawnActor<ARailGun>(railGunRef->GetAuthoritativeClass(), params);
			break;
		}
		default:
		{
			break;
		}
	}

	FAttachmentTransformRules rules{ EAttachmentRule::SnapToTarget, true };
	mPrimaryWeapon->AttachToComponent(Mesh, rules, TEXT("SK_PrimaryWeapon"));
}

void AAcceleratePlayer::CreateSecondaryWeapon(EPickupTypes secondaryType, uint32_t ammo)
{
	FActorSpawnParameters params;
	params.Owner = this;
	switch (secondaryType)
	{
	case EPickupTypes::Missile:
		if (mSecondaryWeapon)
		{
			mSecondaryWeapon->Destroy();
		}
		mSecondaryWeapon = GetWorld()->SpawnActor<AHomingWeapon>(homingWeaponRef->GetAuthoritativeClass(), params);
		if (mSecondaryWeapon)
		{
			mSecondaryWeapon->SetAmmo(ammo);
		}
		mSecondaryWeapon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform, TEXT("SK_HomingWeapon"));
		break;

	case EPickupTypes::Phase:
		if (mSecondaryWeapon)
		{
			mSecondaryWeapon->Destroy();
		}
		mSecondaryWeapon = GetWorld()->SpawnActor<APhaseWeapon>(phaseWeaponRef->GetAuthoritativeClass(), params);
		if (mSecondaryWeapon)
		{
			mSecondaryWeapon->SetAmmo(ammo);
		}
		mSecondaryWeapon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform, TEXT("SK_HomingWeapon"));
		mSecondaryWeapon->SetOwningPlayer(this);
		break;

	case EPickupTypes::Flash:
		if (mSecondaryWeapon)
		{
			mSecondaryWeapon->Destroy();
		}
		mSecondaryWeapon = GetWorld()->SpawnActor<AFlashWeapon>(flashWeaponRef->GetAuthoritativeClass(), params);
		if (mSecondaryWeapon)
		{
			mSecondaryWeapon->SetAmmo(ammo);
		}
		mSecondaryWeapon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform, TEXT("SK_HomingWeapon"));
		mSecondaryWeapon->SetOwningPlayer(this);
		break;

	case EPickupTypes::RPG:
		if (mSecondaryWeapon)
		{
			mSecondaryWeapon->Destroy();
		}
		mSecondaryWeapon = GetWorld()->SpawnActor<ARPGWeapon>(rpgWeaponRef->GetAuthoritativeClass(), params);
		if (mSecondaryWeapon)
		{
			mSecondaryWeapon->SetAmmo(ammo);
		}
		mSecondaryWeapon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform, TEXT("SK_HomingWeapon"));
		break;

	case EPickupTypes::DomeShield:
		if (mSecondaryWeapon)
		{
			mSecondaryWeapon->Destroy();
		}
		mSecondaryWeapon = GetWorld()->SpawnActor<ADomeShield>(domeShieldRef->GetAuthoritativeClass(), params);
		mSecondaryWeapon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform, TEXT("SK_DomeShield"));
		mSecondaryWeapon->SetOwningPlayer(this);
		break;
	case EPickupTypes::Hook:
		if (mSecondaryWeapon)
		{
			mSecondaryWeapon->Destroy();
		}
		mSecondaryWeapon = GetWorld()->SpawnActor<AHook>();
		if (mSecondaryWeapon)
		{
			mSecondaryWeapon->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
			mSecondaryWeapon->SetActorRelativeLocation(FVector(0.0f));
			mSecondaryWeapon->SetAmmo(ammo);
			mSecondaryWeapon->SetOwningPlayer(this);
		}
		break;
	case EPickupTypes::Mine:
		if (mSecondaryWeapon)
		{
			mSecondaryWeapon->Destroy();
		}
		mSecondaryWeapon = GetWorld()->SpawnActor<AMineWeapon>(MineRef->GetAuthoritativeClass(), params);
		if (mSecondaryWeapon)
		{
			mSecondaryWeapon->SetAmmo(ammo);
		}
		mSecondaryWeapon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform, TEXT("SK_MineWeapon"));
		break;
	case EPickupTypes::Drain:
		if (mSecondaryWeapon)
		{
			mSecondaryWeapon->Destroy();
		}
		mSecondaryWeapon = GetWorld()->SpawnActor<ADrainWeapon>(DrainRef->GetAuthoritativeClass(), params);
		if (mSecondaryWeapon)
		{
			mSecondaryWeapon->SetAmmo(ammo);
		}
		mSecondaryWeapon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform, TEXT("SK_DrainWeapon"));
		break;
	case EPickupTypes::EMP:
		if (mSecondaryWeapon)
		{
			mSecondaryWeapon->Destroy();
		}
		mSecondaryWeapon = GetWorld()->SpawnActor<AEMP>();
		if (mSecondaryWeapon)
		{
			mSecondaryWeapon->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
			mSecondaryWeapon->SetActorRelativeLocation(FVector(0.0f));
			mSecondaryWeapon->SetAmmo(ammo);
			mSecondaryWeapon->SetOwningPlayer(this);
		}
		break;
	default:
		break;
	}
}

void AAcceleratePlayer::SetBoostFromPickup(float boost)
{
	if (boost <= this->mBoostMax)
	{
		this->mBoostCurrent += boost;
		if (this->mBoostCurrent >= this->mBoostMax)
		{
			this->mBoostCurrent = this->mBoostMax;
		}
	}
}

void AAcceleratePlayer::SetHealthFromPickup(float health)
{
	if (health <= MaxHealth)
	{
		Health += health;
		if (Boost >= MaxHealth)
		{
			Boost = MaxHealth;
		}
	}
}

void AAcceleratePlayer::SetIsDoubleDamage(bool isDoubDam)
{
	if (mSecondaryWeapon)
	{
		mSecondaryWeapon->mIsDoubleDamage = isDoubDam;
	}
	if (mPrimaryWeapon)
	{
		mPrimaryWeapon->mIsDoubleDamage = isDoubDam;
	}
}

void AAcceleratePlayer::SetIsDoublePoints(bool isDoubPoints)
{
	mIsDoublePoints = isDoubPoints;
}

void AAcceleratePlayer::CreateWeaponPickupTest()
{
	CreateSecondaryWeapon(EPickupTypes::DomeShield, 1);
}

void AAcceleratePlayer::AddPoints(float points)
{
	mPlayerPoints += points;
}


float AAcceleratePlayer::GetPlayerPoints()
{
	return mPlayerPoints;
}

void AAcceleratePlayer::SetPlayerFOV()
{
	UGameManager* gameManager = Cast<UGameManager>(GetGameInstance());

	if (gameManager->GetNumberOfPlayers() == 2)
	{
		if (this == gameManager->GetPlayer(0) || this == gameManager->GetPlayer(1))
		{
			Camera->SetFieldOfView(120.0f);
		}
	}
	else if (gameManager->GetNumberOfPlayers() == 3)
	{
		if (this == gameManager->GetPlayer(0))
		{
			Camera->SetFieldOfView(120.0f);
		}
	}
}