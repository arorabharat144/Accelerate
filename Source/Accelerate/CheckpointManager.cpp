// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckpointManager.h"
#include "EngineUtils.h"
#include "Engine/Engine.h"
#include "Components/StaticMeshComponent.h"
#include "AIPlayer.h"
#include "AcceleratePlayer.h"
#include "Checkpoint.h"
#include "GameManager.h"
#include "EngineGlobals.h"


// Sets default values
ACheckpointManager::ACheckpointManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACheckpointManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACheckpointManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mCheckpoints.Num() != 0 && mPlayers.Num() != 0)
	{
		UpdatePlayerPositions(DeltaTime);

		for (auto& player : mPlayers)
		{
			if (player->Health <= 0.0f || player->GetActorLocation().Z <= HeightToRespawn)
			{
				RespawnPlayer(player);
			}

			if (!player->IsA(AAIPlayer::StaticClass()))
			{
				UE_LOG(LogTemp, Display, TEXT("Position: %i"), GetPlayerPosition(player));
			}
		}
	}
}

void ACheckpointManager::Init()
{
	for (TActorIterator<ACheckpoint> checkpoint(GetWorld()); checkpoint; ++checkpoint)
	{
		mCheckpoints.Add(*checkpoint);
	}
	int i, j;
	for (i = 0; i < mCheckpoints.Num() - 1; i++)
	{
		for (j = 0; j < mCheckpoints.Num() - i - 1; j++)
		{
			if (mCheckpoints[j]->checkpointNumber > mCheckpoints[j + 1]->checkpointNumber)
			{
				ACheckpoint* temp = mCheckpoints[j];
				mCheckpoints[j] = mCheckpoints[j + 1];
				mCheckpoints[j + 1] = temp;
			}
		}
	}

	for (TActorIterator<AAcceleratePlayer> player(GetWorld()); player; ++player)
	{
		mPlayers.Add(*player);
		mLastCheckpoints.Add(*player, mCheckpoints.Last());
	}


	PlayerStats defaultPlayerStats;
	
	if (mCheckpoints.Num() != 0 && mPlayers.Num() != 0)
	{
		for (auto& checkpoint : mCheckpoints)
		{
			defaultPlayerStats.Add(checkpoint, 0);
		}

		for (auto& player : mPlayers)
		{
			mPlayerStats.Add(player, defaultPlayerStats);
			mNextCheckpoints.Add(player, mCheckpoints[0]);
			mPlayerPositions.Add(player, 1);
		}
	}
}

void ACheckpointManager::RespawnPlayer(AAcceleratePlayer* player)
{
	FVector newLocation = mLastCheckpoints[player]->GetActorLocation();
	newLocation.Z += 100.0f;
	player->SetActorLocationAndRotation(newLocation, mLastCheckpoints[player]->GetActorRotation());
	player->Health = player->MaxHealth;
	player->Mesh->SetPhysicsLinearVelocity(FVector(0.0f));
	if (player->IsA(AAIPlayer::StaticClass()))
	{
		Cast<AAIPlayer>(player)->SetCurrentCheckpoint
		(mLastCheckpoints[player]->nextAICheckpoints[Cast<AAIPlayer>(player)->pathNumber]);
	}
}

void ACheckpointManager::SetCheckpoint(AAcceleratePlayer* player, ACheckpoint* checkpoint)
{
	mLastCheckpoints[player] = checkpoint;
	if (mNextCheckpoints[player]->checkpointNumber == checkpoint->checkpointNumber)
	{
		mPlayerStats[player][checkpoint]++;
		if (checkpoint->checkpointNumber == mCheckpoints.Num() - 1)
		{
			mNextCheckpoints[player] = mCheckpoints[0];
		}
		else
		{
			mNextCheckpoints[player] = mCheckpoints[checkpoint->checkpointNumber + 1];
		}
	}
}


void ACheckpointManager::UpdatePlayerPositions(float deltaTime)
{
	static const float UPDATE_WAIT_TIME = 0.3f;
	static float updateTimer = 0.0f;

	updateTimer += deltaTime;

	if (updateTimer >= UPDATE_WAIT_TIME)
	{
		updateTimer = 0.0f;
		
		//Actual Player Position update
		TMap<float, AAcceleratePlayer*> playerPercentages;
		TArray<float> sortedPercentages;

		for (auto player : mPlayers)
		{
			if (player->IsA(AAIPlayer::StaticClass()))
			{
				continue;
			}

			float percentage = 0.0f, distToLastCheckpoint = 0.0f, distFromLastToNextCheckpoint = 0.0f;

			distToLastCheckpoint = FVector::DistSquared(player->GetActorLocation(), 
				mLastCheckpoints[player]->GetActorLocation());

			distFromLastToNextCheckpoint = FVector::DistSquared(mLastCheckpoints[player]->GetActorLocation(),
				mNextCheckpoints[player]->GetActorLocation());

			percentage = (GetPlayerLapCount(player) * mCheckpoints.Num()) + mLastCheckpoints[player]->checkpointNumber +
				(distToLastCheckpoint / distFromLastToNextCheckpoint);

			percentage = percentage / ((LapCount * mCheckpoints.Num()) + mCheckpoints.Num() + 1);

			while (sortedPercentages.Contains(percentage))
			{
				percentage += 0.01f;
			}

			playerPercentages.Add(percentage, player);
			sortedPercentages.Add(percentage);
		}

		
		int i, j;
		for (i = 0; i < sortedPercentages.Num() - 1; i++)
		{
			for (j = 0; j < sortedPercentages.Num() - i - 1; j++)
			{
				if (sortedPercentages[j] > sortedPercentages[j + 1])
				{
					float temp = sortedPercentages[j];
					sortedPercentages[j] = sortedPercentages[j + 1];
					sortedPercentages[j + 1] = temp;
				}
			}
		}

		int position = 1;
		for (auto percent : sortedPercentages)
		{
			mPlayerPositions[playerPercentages[percent]] = position;
			position++;
		}
	}

}