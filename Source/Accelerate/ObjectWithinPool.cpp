// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectWithinPool.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"


// Sets default values
AObjectWithinPool::AObjectWithinPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorEnableCollision(true);

}

void AObjectWithinPool::SetLifeSpan(float InLifeSpan)
{
	mLifeSpan = InLifeSpan;
	GetWorldTimerManager().SetTimer(mLifeSpanTimer, this, &AObjectWithinPool::Deactivate, mLifeSpan, false);
}

void AObjectWithinPool::SetActive(bool isActive)
{
	mISActive = isActive;	
	SetActorHiddenInGame(!mISActive);
}

bool AObjectWithinPool::IsActive() const
{
	return mISActive;
}

// Called when the game starts or when spawned
void AObjectWithinPool::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjectWithinPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectWithinPool::Deactivate()
{
	SetActive(false);
}

