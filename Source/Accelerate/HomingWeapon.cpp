// Fill out your copyright notice in the Description page of Project Settings.

#include "HomingWeapon.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMath.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Core/Public/Misc/OutputDeviceNull.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "HomingMissile.h"
#include "ObjectsSpawner.h"

// Sets default values
AHomingWeapon::AHomingWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Construct static mesh component
	homingWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HomingWeaponMesh"));
	RootComponent = homingWeaponMesh;

	muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	muzzle->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHomingWeapon::BeginPlay()
{
	/*Super::BeginPlay();
	TArray<AActor*> spawners;
	UWorld* world = GetWorld();

	UGameplayStatics::GetAllActorsOfClass(world, AObjectsSpawner::StaticClass(), spawners);

	for (AActor* spawner : spawners)
	{
		missileSpawner = Cast<AObjectsSpawner>(spawner);

		if (missileSpawner != nullptr)
		{
			if (missileSpawner->GetSpawnerName() == "HomingMissileSpawner")
			{
				break;
			}
		}
	}*/

}

// Called every frame
void AHomingWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AHomingWeapon::Fire()
{
	//If it has ammo
	if (GetAmmo() > 0)
	{
		if (missileRef != nullptr)
		{
			UWorld* const world{ GetWorld() };
			if (world != nullptr)
			{
				FActorSpawnParameters spawnParams;
				spawnParams.Owner = this;

				FRotator rotation;
				FVector spawnLocation = muzzle->GetComponentLocation();

				AHomingMissile* firedMissile = world->SpawnActorDeferred<AHomingMissile>(missileRef.Get(), muzzle->GetComponentTransform(), this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
				firedMissile->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

				UGameplayStatics::FinishSpawningActor(firedMissile, muzzle->GetComponentTransform());

			}
		}
		

		
		//FVector spawnLocation = muzzle->GetRelativeTransform().GetLocation();
		//FRotator rotation;

		//AHomingMissile* firedMissile = Cast<AHomingMissile>(missileSpawner->Spawn(spawnLocation, rotation));

		//if (firedMissile != nullptr)
		//{
		//	
		//	firedMissile->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		//	FOutputDeviceNull ar;
		//	const FString command = FString::Printf(TEXT("EnableMissile %s"), *this->GetName());
		//	firedMissile->CallFunctionByNameWithArguments(*command, ar, NULL, true);

		//	//Reduce 1 ammo
			SetAmmo(GetAmmo() - 1);
			if (GetAmmo() <= 0)
			{
				Destroy();
			}

		//	firedMissile->AttachToActor(NULL, FAttachmentTransformRules::KeepRelativeTransform);

		//}
	}
}