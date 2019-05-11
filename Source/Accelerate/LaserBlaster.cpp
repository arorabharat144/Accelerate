// Fill out your copyright notice in the Description page of Project Settings.

#include "LaserBlaster.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/Classes/Engine/BlueprintCore.h"
#include "Runtime/Engine/Classes/Components/ArrowComponent.h"

ALaserBlaster::ALaserBlaster()
{

}

void ALaserBlaster::BeginPlay()
{
	Super::BeginPlay();
	
}


void ALaserBlaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	mCurrentCadency += GetWorld()->GetDeltaSeconds();
}

void ALaserBlaster::Fire(float value)
{

	if (value > 0.0f)
	{
		if (mCurrentCadency > mMaxCadency && mCurrentHeatLevel < mMaxHeatLevel)
		{
			//Reduce the heat level of the weapon
			IncrementHeatLevel();
			this->LaserBlasterFireEvent();
			mCurrentCadency = 0.0f;
		}
	}
	else
	{
		DecrementHeatLevel();
	}
}

FString ALaserBlaster::GetBlueprintPath()
{
	return FString("Blueprint'/Game/BluePrints/BaseWeapons/BP_LaserBlaster69.BP_LaserBlaster69'");
}

