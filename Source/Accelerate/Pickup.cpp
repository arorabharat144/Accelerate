// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"
#include "Engine/Classes/Engine/Engine.h"
#include "AIPlayer.h"
#include "AcceleratePlayer.h"

#include "Components/BoxComponent.h"

// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//All pickups starts being able to be picked
	mIsActive = true;


	//Set current pickup type, change later to use polymorphic structure of pickups for different behaviour

	//Set the Meshes
	mPickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = mPickupMesh;

	mPickupCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupCollider"));
	mPickupCollider->SetWorldScale3D(FVector(35.0f, 7.0f, 7.0f));
	mPickupCollider->SetHiddenInGame(true);
	mPickupCollider->BodyInstance.SetCollisionProfileName(TEXT("OverlapAll"));
	mPickupCollider->SetNotifyRigidBodyCollision(true);
	mPickupCollider->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlapBegin);
	mPickupCollider->OnComponentEndOverlap.AddDynamic(this, &APickup::OnOverlapEnd);
	mPickupCollider->CurrentTag = 5;
	mPickupCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (mOverlappedPlayer && mIsActive)
	{
		if (mPickupType == EPickupTypes::Boost)
		{
			UE_LOG(LogTemp, Warning, TEXT("Pickup Boost"));
			mOverlappedPlayer->SetBoostFromPickup(Boost);
		}
		else if (mPickupType == EPickupTypes::Health)
		{
			UE_LOG(LogTemp, Warning, TEXT("Pickup Health"));
			mOverlappedPlayer->SetHealthFromPickup(Health);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Pickup Weapon"));
			mOverlappedPlayer->CreateSecondaryWeapon(mPickupType, Ammo);
		}
	}
	
}

void APickup::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && OtherActor->IsA(AAcceleratePlayer::StaticClass()))
	{
		mOverlappedPlayer = static_cast<AAcceleratePlayer*>(OtherActor);
		if (mOverlappedPlayer && mIsActive && !mOverlappedPlayer->IsA(AAIPlayer::StaticClass()))
		{
			if (mPickupType == EPickupTypes::Boost)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::FromInt(Boost));
				mOverlappedPlayer->SetBoostFromPickup(Boost);
				mIsActive = false;
				mPickupMesh->ToggleVisibility(true);
				GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &APickup::ResetPickup, SpwanTime, false);
			}
			else if (mPickupType == EPickupTypes::Health)
			{
				//GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, FString::FromInt(Health));
				mOverlappedPlayer->SetHealthFromPickup(Health);
				mIsActive = false;
				mPickupMesh->ToggleVisibility(true);
				GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &APickup::ResetPickup, SpwanTime, false);
			}
			else if (mPickupType == EPickupTypes::DoubleDamage)
			{
				mOverlappedPlayer->SetIsDoubleDamage(true);
				if (mOverlappedPlayer->mPrimaryWeapon)
				{
					GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Black, FString::FromInt(mOverlappedPlayer->mPrimaryWeapon->mIsDoubleDamage));
				}
				mIsActive = false;
				mPickupMesh->ToggleVisibility(true);
				GetWorld()->GetTimerManager().SetTimer(durationTimerHandle, this, &APickup::EndOfDuration, DoubleDamageDuration, false);
				GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &APickup::ResetPickup, SpwanTime, false);

			}
			else if (mPickupType == EPickupTypes::DoublePoints)
			{
				mOverlappedPlayer->SetIsDoublePoints(true);
				GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Blue, FString::FromInt(mOverlappedPlayer->mIsDoublePoints));
				mIsActive = false;
				mPickupMesh->ToggleVisibility(true);
				GetWorld()->GetTimerManager().SetTimer(durationTimerHandle, this, &APickup::ResetPickup, DoublePointsDuration, false);
				GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &APickup::ResetPickup, SpwanTime, false);

			}
			else if (mPickupCategory == EPickupCategories::OffensiveWeapon)
			{
				mOverlappedPlayer->CreateSecondaryWeapon(mPickupType, Ammo);
				RandomizePickupTypes();
				mIsActive = false;
				mPickupMesh->ToggleVisibility(true);
				GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &APickup::ResetPickup, SpwanTime, false);
			}
			else if (mPickupCategory == EPickupCategories::DefensiveWeapon)
			{
				mOverlappedPlayer->CreateSecondaryWeapon(mPickupType, Ammo);
				RandomizePickupTypes();
				mIsActive = false;
				mPickupMesh->ToggleVisibility(true);
				GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &APickup::ResetPickup, SpwanTime, false);
			}
			else
			{
				return;
			}
		}
	}
}

void APickup::RandomizePickupTypes()
{
	switch (mPickupCategory)
	{
	case EPickupCategories::DefensiveWeapon:
	{
		mPickupType = static_cast<EPickupTypes>(FMath::RandRange((int)EPickupTypes::Mine, (int)EPickupTypes::EMP));
		break;
	}
	case EPickupCategories::OffensiveWeapon:
	{
		mPickupType = static_cast<EPickupTypes>(FMath::RandRange((int)EPickupTypes::Missile, (int)EPickupTypes::Hook));
		break;
	}
	default:
	{
		// this shouldnt happen but if it does its health
		mPickupType = EPickupTypes::Health;
		break;
	}
	}
}

void APickup::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != this && OtherActor->IsA(AAcceleratePlayer::StaticClass()))
	{
		mOverlappedPlayer = nullptr;
	}
}

//Reset Pickup
void APickup::ResetPickup()
{
	mIsActive = true;
	mPickupMesh->ToggleVisibility(false);
	GetWorld()->GetTimerManager().ClearTimer(timerHandle);

}

void APickup::EndOfDuration()
{
	mOverlappedPlayer->SetIsDoubleDamage(false);
	mOverlappedPlayer->SetIsDoublePoints(false);
	GetWorld()->GetTimerManager().ClearTimer(durationTimerHandle);

}

//Return mIsActiveState
bool APickup::IsActive()
{
	return mIsActive;
}

//Change mIsActiveState
void APickup::SetActive(bool PickupState)
{
	mIsActive = PickupState;
}

EPickupTypes APickup::GetPickupType() const
{
	return mPickupType;
}

void APickup::WasCollected_Implementation()
{
	//Function just to print the name of the pickup.
	//If you want to override this function but want to print the name anyway,
	//instead of repeat the same code, on the child class you just have to call
	//Super::WasCollected_Implementation();
	//And them, apply your own logic.
	FString PickupDebugString = GetName();
	UE_LOG(LogClass, Log, TEXT("You have collected %s"), *PickupDebugString);
}