// Fill out your copyright notice in the Description page of Project Settings.

#include "FlashWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "AcceleratePlayer.h"

AFlashWeapon::AFlashWeapon()
{

}

void AFlashWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AFlashWeapon::Tick(float DeltaTime)
{
	Super::BeginPlay();
}

void AFlashWeapon::Fire()
{
	if (GetAmmo() > 0)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACar::StaticClass(), FoundActors);
		for (auto& actor : FoundActors)
		{
			AAcceleratePlayer* playerRef = Cast<AAcceleratePlayer>(actor);
			if (playerRef != nullptr && playerRef != GetOwningPlayer())
			{
				playerRef->ActivateFlash();
			}
		}
		SetAmmo(GetAmmo() - 1);
	}
	else
	{
		Destroy();
	}
}