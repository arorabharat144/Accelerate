// Fill out your copyright notice in the Description page of Project Settings.

#include "RailGun.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/Classes/Engine/BlueprintCore.h"
#include "Runtime/Engine/Classes/Components/ArrowComponent.h"

// Sets default values
ARailGun::ARailGun()
{

}

// Called when the game starts or when spawned
void ARailGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARailGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	mCurrentCadency += GetWorld()->GetDeltaSeconds();
}

void ARailGun::Fire(float value)
{

	if (value > 0.0f)
	{
		if (mCurrentCadency > mMaxCadency && mCurrentHeatLevel < mMaxHeatLevel)
		{
			//Reduce the heat level of the weapon
			IncrementHeatLevel();
			this->RailGunBlasterFireEvent();
			mCurrentCadency = 0.0f;
		}
	}
	else
	{
		DecrementHeatLevel();
	}
}

FString ARailGun::GetBlueprintPath()
{
	return FString("Blueprint'/Game/BluePrints/BaseWeapons/BP_LaserBlaster69.BP_LaserBlaster69'");
}

