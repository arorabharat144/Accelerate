// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "vector"
#include "map"
#include "CheckpointManager.generated.h"

class AAcceleratePlayer;
class ACheckpoint;

using PlayerStats = TMap<ACheckpoint*, int>;

UCLASS()
class ACCELERATE_API ACheckpointManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpointManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init();

	void RespawnPlayer(AAcceleratePlayer* player);

	void SetCheckpoint(AAcceleratePlayer* player, ACheckpoint* checkpoint);

	void UpdatePlayerPositions(float deltaTime);

	UPROPERTY(EditAnywhere, Category = "CheckpointManagerProperties")
	float HeightToRespawn{ -1900.0f };

	UPROPERTY(BlueprintReadOnly, Category="CheckpointManagerProperties")
	int LapCount{3};

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		int GetPlayerLapCount(AAcceleratePlayer* player) const { return mPlayerStats[player][mCheckpoints.Last()] + 1; }

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
	int GetPlayerPosition(AAcceleratePlayer* player) const { return mPlayerPositions[player]; }


private:
	TArray<ACheckpoint*> mCheckpoints;
	TArray<AAcceleratePlayer*> mPlayers;
	TMap<AAcceleratePlayer*, ACheckpoint*> mLastCheckpoints;
	TMap<AAcceleratePlayer*, ACheckpoint*> mNextCheckpoints;
	TMap<AAcceleratePlayer*, PlayerStats> mPlayerStats;
	TMap<AAcceleratePlayer*, int> mPlayerPositions;
	bool mInitialized{ false };
};
