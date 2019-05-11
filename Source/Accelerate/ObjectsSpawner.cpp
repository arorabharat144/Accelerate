// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectsSpawner.h"
#include "Engine/Classes/Components/BoxComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Sets default values
AObjectsSpawner::AObjectsSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mSpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = mSpawnVolume;

	ObjectPooler = CreateDefaultSubobject<UObjectPool>(TEXT("ObjectPooler"));


}

// Called when the game starts or when spawned
void AObjectsSpawner::BeginPlay()
{
	Super::BeginPlay();
	ObjectPooler->CreateObjects();
}

// Called every frame
void AObjectsSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AObjectWithinPool* AObjectsSpawner::Spawn(FVector position, FRotator rotation)
{
	AObjectWithinPool* poolableActor = ObjectPooler->GetObjectInPool();
	if (poolableActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot Spawn"));
		return nullptr;
	}
	poolableActor->SetActorLocation(position);
	poolableActor->SetActive(true);
	poolableActor->SetActorRotation(rotation);
	return poolableActor;
	UE_LOG(LogTemp, Warning, TEXT("Spawning"));
}

FString AObjectsSpawner::GetSpawnerName()
{
	return mSpawnerName;
}
