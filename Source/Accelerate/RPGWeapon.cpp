// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGWeapon.h"
#include "RPGMissile.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMath.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ARPGWeapon::ARPGWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Construct static mesh component
	rpgWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HomingWeaponMesh"));
	RootComponent = rpgWeaponMesh;

	muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	muzzle->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARPGWeapon::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARPGWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ARPGWeapon::Fire()
{
	//If it has ammo
	if (GetAmmo() > 0)
	{
		if (rpgRef != nullptr)
		{
			UWorld* const world{ GetWorld() };
			if (world != nullptr)
			{
				FActorSpawnParameters spawnParams;
				spawnParams.Owner = this;

				FRotator rotation;
				FVector spawnLocation = muzzle->GetComponentLocation();

				ARPGMissile* firedMissile = world->SpawnActorDeferred<ARPGMissile>(rpgRef.Get(), muzzle->GetComponentTransform(), this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
				firedMissile->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

				UGameplayStatics::FinishSpawningActor(firedMissile, muzzle->GetComponentTransform());
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
