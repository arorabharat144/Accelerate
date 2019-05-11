// Fill out your copyright notice in the Description page of Project Settings.

#include "MineWeapon.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Mine.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMath.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


AMineWeapon::AMineWeapon()

{
	PrimaryActorTick.bCanEverTick = true;

	MineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MineWeaponMesh"));

	RootComponent = MineMesh;

	Spawn = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnLoc"));
	Spawn->SetupAttachment(RootComponent);
}

void AMineWeapon::BeginPlay()
{
	Super::BeginPlay();
}
void AMineWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMineWeapon::Fire()
{
	if (GetAmmo() > 0)
	{
		if (mineRef != nullptr)
		{
			UWorld* const world{ GetWorld() };
			if (world != nullptr)
			{
				FVector spawnlocation = Spawn->GetComponentLocation();

				AMine* DroppedMine = world->SpawnActorDeferred<AMine>(mineRef.Get(), Spawn->GetComponentTransform(), this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
				DroppedMine->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

				UGameplayStatics::FinishSpawningActor(DroppedMine, Spawn->GetComponentTransform());

			}

		}
		SetAmmo(GetAmmo() - 1);
		if (GetAmmo() <= 0)
		{
			Destroy();
		}
	}
}
