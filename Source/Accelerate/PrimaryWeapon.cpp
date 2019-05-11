// Fill out your copyright notice in the Description page of Project Settings.

#include "PrimaryWeapon.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
APrimaryWeapon::APrimaryWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void APrimaryWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APrimaryWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APrimaryWeapon::Fire(float value)
{
	UE_LOG(LogClass, Log, TEXT("Firing..."));
}

void APrimaryWeapon::Reload()
{
	UE_LOG(LogClass, Log, TEXT("Reloading..."));
}

void APrimaryWeapon::IncrementHeatLevel()
{
	mCurrentHeatLevel += mHeatIncrement;
	if (mCurrentHeatLevel > mMaxHeatLevel)
	{
		mCurrentHeatLevel = mMaxHeatLevel;
	}
}

void APrimaryWeapon::DecrementHeatLevel()
{
	mCurrentHeatLevel -= mCoolDownDecrement;
	if (mCurrentHeatLevel < 0.0f)
	{
		mCurrentHeatLevel = 0.0f;
	}
}