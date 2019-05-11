// Fill out your copyright notice in the Description page of Project Settings.

#include "DrainWeapon.h"
#include "Drain.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"

ADrainWeapon::ADrainWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	DrainWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DrainWeaponMesh"));
	RootComponent = DrainWeaponMesh;

	Spawn = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn"));
	Spawn->SetupAttachment(RootComponent);

}

void ADrainWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ADrainWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ADrainWeapon::Fire()
{
	if (GetAmmo() > 0)
	{
		if (drainRef != nullptr)
		{
			UWorld* const world{ GetWorld() };
			if (world != nullptr)
			{
				FActorSpawnParameters spawnParams;
				spawnParams.Owner = this;

				FRotator rotation;
				FVector spawnLocation = Spawn->GetComponentLocation();

				ADrain* fired = world->SpawnActorDeferred<ADrain>(drainRef.Get(), Spawn->GetComponentTransform(), this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
				fired->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

				UGameplayStatics::FinishSpawningActor(fired, Spawn->GetComponentTransform());
			}
		}

		//Reduce 1 ammo
		SetAmmo(GetAmmo() - 1);
		if (GetAmmo() <= 0)
		{
			Destroy();
		}
	}
}