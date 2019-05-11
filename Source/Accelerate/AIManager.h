// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AICheckpoint.h"
#include <vector>
#include "AIManager.generated.h"


constexpr int MAX_AI = 11;

UENUM()
enum class AIPlayerActions
{
	Left	UMETA(DisplayName = "Left"),
	Right	UMETA(DisplayName = "Right"),
	Nothing	UMETA(DisplayName = "Nothing"),
};

UENUM()
enum class BattleAIStates
{
	Patrol	UMETA(DisplayName = "Patrol"),
	Attack	UMETA(DisplayName = "Attack"),
};

class AAcceleratePlayer;


UCLASS()
class ACCELERATE_API AAIManager : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	AAIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init();


	// Race AI Functions
	AAICheckpoint* RaceUpdate(FVector playerLocation, AAICheckpoint* currentCheckpoint);
	AAICheckpoint* GetCheckpoint(uint32 path, uint32 checkpoint);

	// Battle AI Functions
	AAICheckpoint* BattleUpdate(AAICheckpoint* currentCheckpoint, FVector currentLocation, int& iterate);
	AAcceleratePlayer* GetTarget(FVector currentLocation, float heightDifference);

	// Functions for Race and Battle AI
	AIPlayerActions GetAction(FVector direction, FVector location, FVector targetLocation) const;

	//UPROPERTY(EditAnywhere, Category = "Designer Tools")
	float checkpointCollideDistance{ 1500.0f };

private:
	bool mInit{ false };
	std::vector<std::vector<AAICheckpoint*>> mCheckpoints;
	TArray<AAcceleratePlayer*> mPlayers;
};
