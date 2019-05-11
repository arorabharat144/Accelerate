// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectPool.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "ObjectWithinPool.h"

// Sets default values for this component's properties
UObjectPool::UObjectPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


AObjectWithinPool * UObjectPool::GetObjectInPool()
{
	for (AObjectWithinPool* PoolableActor : mPool)
	{
		if (!PoolableActor->IsActive())
		{
			return PoolableActor;
		}
	}
	return nullptr;
}

// Called when the game starts
void UObjectPool::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UObjectPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjectPool::CreateObjects()
{
	if (mPooledObjectSubclass != NULL)
	{
		UWorld* const world = GetWorld();
		if (world)
		{
			for (uint32 i = 0; i < mSize; ++i)
			{
				AObjectWithinPool* PoolableActor = world->SpawnActor<AObjectWithinPool>(
					mPooledObjectSubclass,
					FVector(0.0f, i*2000.0f, 0.0f),
					FRotator::ZeroRotator);
				PoolableActor->SetActive(false);
				mPool.Add(PoolableActor);
			}
		}
	}
}
