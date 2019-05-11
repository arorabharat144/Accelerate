// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ObjectPool.h"
#include "ObjectWithinPool.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectsSpawner.generated.h"

class UBoxComponent;
UCLASS()
class ACCELERATE_API AObjectsSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectsSpawner();

private:
	float GetLifeSpawn();
	class UBoxComponent* mSpawnVolume;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	UObjectPool* ObjectPooler;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	FString mSpawnerName;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	bool trigger;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float lifeSpan = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float spawnCoolDown = 1.0f;

	FTimerHandle SpawnCoolDownTimer;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	AObjectWithinPool* Spawn(FVector position = FVector::ZeroVector, FRotator rotation = FRotator::ZeroRotator);

	UFUNCTION(BlueprintCallable)
	FString GetSpawnerName();
};
