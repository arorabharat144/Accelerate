// Fill out your copyright notice in the Description page of Project Settings.

#include "RaceManager.h"

#include "Classes/Kismet/GameplayStatics.h"
#include "Classes/Engine/World.h"
#include "Classes/GameFramework/PlayerStart.h"

#include "GameManager.h"
#include "CarController.h"
#include "AcceleratePlayer.h"

#include "CheckpointManager.h"
#include "AIManager.h"

#include "ModeTypeContainers.h"

#include "AccelerateUtility.h"

ARaceManager::ARaceManager()
{
	PrimaryActorTick.bCanEverTick = true;

	for (int32 i{ 0 }; i < AccelerateUtility::GetEnumSize("EMaps"); ++i)
	{
		lapCount.Emplace(static_cast<EMaps>(i));
	}
}

void ARaceManager::BeginPlay()
{
	Super::BeginPlay();

	UGameManager* gameManager{ Cast<UGameManager>(GetGameInstance()) };

	gameManager->mPlayers.Empty();

	UWorld* world{ GetWorld() };

	if (!gameManager->debugMode)
	{
		//for (uint32 i{ static_cast<uint32>(gameManager->GetMaximumPlayerCount()) }; i > static_cast<uint32_t>(gameManager->GetNumberOfPlayers()); --i)
		//{
		//	gameManager->mPlayerControllers.RemoveAt(i - 1);
		//}
	}
	else
	{
		gameManager->SetNumberOfPlayers(debugCarTypes.Num());

		gameManager->mPlayerControllers.Add(world->GetFirstPlayerController());

		if (gameManager->GetNumberOfPlayers() > 1)
		{
			for (uint32 i{ 0 }; i < static_cast<uint32_t>(gameManager->GetNumberOfPlayers() - 1); ++i)
			{
				gameManager->mPlayerControllers.Add(UGameplayStatics::CreatePlayer(world));
			}
		}

		gameManager->SetCurrentMap(currentMap);

	}

	world->GetGameViewport()->SetDisableSplitscreenOverride(false);

	TSharedPtr<RaceModeType> raceMode{ StaticCastSharedPtr<RaceModeType>(gameManager->GetSelectedMode()) };
	
	//mCheckpointManager = NewObject<ACheckpointManager>(this, checkpointManagerRef->GetAuthoritativeClass());
	//mAIManager = NewObject<AAIManager>(this);
	checkpointManager = world->SpawnActor<ACheckpointManager>(checkpointManagerRef->GetAuthoritativeClass());
	checkpointManager->Init();

	checkpointManager->LapCount = lapCount.FindRef(gameManager->GetCurrentMap());

	mAIManager = world->SpawnActor<AAIManager>();

	//TArray<int32> ids;
	//gameManager->GetSelectedPrimaryOffensiveWeapons().GetKeys(ids);

	for (uint32 i{ 0 }; i < static_cast<uint32>(gameManager->GetNumberOfPlayers()); ++i)
	{
		gameManager->mPlayerControllers[i] = Cast<ACarController>(UGameplayStatics::GetPlayerController(world, i));
		Cast<ACarController>(gameManager->mPlayerControllers[i])->CreateRaceHUD();

		Cast<ACarController>(gameManager->mPlayerControllers[i])->CreatePauseMenu();

		gameManager->mPlayers.Add(Cast<AAcceleratePlayer>(gameManager->mPlayerControllers[i]->GetPawn()));

		ECarTypes currentCarType;
		if (!gameManager->debugMode)
		{
			currentCarType = AccelerateUtility::GetEnumFromString<ECarTypes, uint8>({"ECarTypes"}, raceMode->raceCarValues[i].model);
			//gameManager->mPlayers[i]->CreatePrimaryOffensiveWeapon(gameManager->GetSelectedPrimaryOffensiveWeapons().FindRef(ids[i]));
		}
		else
		{
			currentCarType = debugCarTypes[i];
		}
		gameManager->mPlayers[i]->Mesh->SetStaticMesh(availableCarMeshes[currentCarType]);
	}
}

void ARaceManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AActor* ARaceManager::ChoosePlayerStart_Implementation(AController* Player)
{
	if (playerStartAssignCode == 0)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), playerStarts);
	}

	return playerStarts[playerStartAssignCode++];
}