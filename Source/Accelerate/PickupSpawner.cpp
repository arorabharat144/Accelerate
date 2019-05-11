// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupSpawner.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"


// Sets default values
APickupSpawner::APickupSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawner Mesh"));
	RootComponent = SpawnerMesh;

}

// Called when the game starts or when spawned
void APickupSpawner::BeginPlay()
{
	Super::BeginPlay();

	spawnLocation = { this->GetTransform().GetLocation().X + mPickupPosition.X, this->GetTransform().GetLocation().Y + mPickupPosition.Y, this->GetTransform().GetLocation().Z + mPickupPosition.Z};
	spawnRotation = {0,0,0};
	RandomizePickupTypes();
	RandomizeAmmo();
	mPickup->mPickupCategory = mPickupCategory;
	mPickup->mPickupType = mPickupType;

}

// Called every frame
void APickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator pickRotation = { mPickupRotation.Pitch + DeltaTime, mPickupRotation.Yaw + DeltaTime, mPickupRotation.Roll + DeltaTime };
	mPickup->SetActorRotation(pickRotation, ETeleportType::None);
}
/*

*/

void APickupSpawner::RandomizePickupTypes()
{
	switch (mPickupCategory)
	{
	case EPickupCategories::DefensiveWeapon:
	{
		mPickupType = static_cast<EPickupTypes>(FMath::RandRange((int)EPickupTypes::Mine, (int)EPickupTypes::EMP));
		mPickup = GetWorld()->SpawnActor<APickup>(RefDefensivePickup, spawnLocation, spawnRotation, spawnParam);
		break;
	}
	case EPickupCategories::OffensiveWeapon:
	{
		mPickupType = static_cast<EPickupTypes>(FMath::RandRange((int)EPickupTypes::Missile, (int)EPickupTypes::Hook));
		mPickup = GetWorld()->SpawnActor<APickup>(RefOffensivePickup, spawnLocation, spawnRotation, spawnParam);
		break;
	}
	case EPickupCategories::Boost:
	{
		mPickupType = EPickupTypes::Boost;
		mPickup = GetWorld()->SpawnActor<APickup>(RefBoostPickup, spawnLocation, spawnRotation, spawnParam);
		break;
	}
	case EPickupCategories::Health:
	{
		mPickupType = EPickupTypes::Health;
		mPickup = GetWorld()->SpawnActor<APickup>(RefHealthPickup, spawnLocation, spawnRotation, spawnParam);
		break;
	}
	case EPickupCategories::DoubleDamage:
	{
		mPickupType = EPickupTypes::DoubleDamage;
		mPickup = GetWorld()->SpawnActor<APickup>(RefDoubleDamagePickup, spawnLocation, spawnRotation, spawnParam);
		break;
	}
	case EPickupCategories::DoublePoints:
	{
		mPickupType = EPickupTypes::DoublePoints;
		mPickup = GetWorld()->SpawnActor<APickup>(RefDoublePointsPickup, spawnLocation, spawnRotation, spawnParam);
		break;
	}
	default:
	{
		// this shouldnt happen but if it does its health
		mPickupType = EPickupTypes::Health;
		mPickup = GetWorld()->SpawnActor<APickup>(RefHealthPickup, spawnLocation, spawnRotation, spawnParam);
		break;
	}
	}
}

void APickupSpawner::RandomizeAmmo()
{
	switch (mPickupType)
	{
	//DEFENSIVE Weapons
	case EPickupTypes::Mine:
	{
		mPickup->Ammo = FMath::RandRange(AmmoMine.X,AmmoMine.Y);
		break;
	}
	case EPickupTypes::EMP:
	{
		mPickup->Ammo = FMath::RandRange(AmmoEMP.X, AmmoEMP.Y);

		break;
	}
	//OFFENSIVE Weapons
	case EPickupTypes::Missile:
	{
		mPickup->Ammo = FMath::RandRange(AmmoHomingMissile.X, AmmoHomingMissile.Y);

		break;
	}
	case EPickupTypes::RPG:
	{
		mPickup->Ammo = FMath::RandRange(AmmoRPG.X, AmmoRPG.Y);

		break;
	}
	case EPickupTypes::Hook:
	{
		mPickup->Ammo = FMath::RandRange(AmmoHook.X, AmmoHook.Y);

		break;
	}
	case EPickupTypes::Drain:
	{
		mPickup->Ammo = FMath::RandRange(AmmoDrain.X, AmmoDrain.Y);

		break;
	}
	case EPickupTypes::Boost:
	{
		mPickup->Boost = BoostPickupValue;
		break;
	}
	case EPickupTypes::Health:
	{
		mPickup->Health = HealthPickupValue;

		break;
	}
	case EPickupTypes::DoubleDamage:
	{
		mPickup->DoubleDamageDuration = DoubleDamageDuration;

		break;
	}
	case EPickupTypes::DoublePoints:
	{
		mPickup->DoublePointsDuration = DoublePointsDuration;

		break;
	}
	default:
	{
		// this shouldnt happen but if it does Do nothing
		break;
	}
	}
}