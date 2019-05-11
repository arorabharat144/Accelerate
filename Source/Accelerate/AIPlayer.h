// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AcceleratePlayer.h"
#include "AIPlayer.generated.h"

class AAICheckpoint;
class AAIManager;

/**
 * 
 */
UCLASS()
class ACCELERATE_API AAIPlayer : public AAcceleratePlayer
{
	GENERATED_BODY()
public:

	AAIPlayer();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void SetCurrentCheckpoint(uint32 checkpoint);

	void Init();

	UPROPERTY(EditAnywhere, Category = "Designer Tools")
	float idleRespawnTime{ 1.0f };

	UPROPERTY(EditAnywhere, Category = "Designer Tools")
	float idlePassDistance{ 100.0f };

	UPROPERTY(EditAnywhere, Category = "Designer Tools")
	int pathNumber{ 0 };

	UPROPERTY(EditAnywhere, Category = "Designer Tools")
	int startingCheckpoint{ 0 };

private:
	AAIManager* mAIManager{ nullptr };
	AAICheckpoint* mCurrentCheckpoint{ nullptr };
	FVector mLastLocation;
	float mIdleTimer{ 0.0f };
	bool mLastLocationSet{ false };
	bool mInit{ false };
};
