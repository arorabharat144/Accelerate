// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleManager.h"

#include "Classes/Kismet/GameplayStatics.h"
#include "Classes/Engine/World.h"
#include "Classes/GameFramework/PlayerStart.h"

#include "GameManager.h"
#include "CarController.h"
#include "AcceleratePlayer.h"

ABattleManager::ABattleManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABattleManager::BeginPlay()
{
	Super::BeginPlay();

	UGameManager* gameManager{ Cast<UGameManager>(GetGameInstance()) };

	TArray<int32> ids;
	gameManager->GetSelectedPrimaryOffensiveWeapons().GetKeys(ids);

	for (uint32 i{ 0 }; i < static_cast<uint32>(gameManager->GetNumberOfPlayers()); ++i)
	{
		gameManager->mPlayerControllers[i] = Cast<ACarController>(UGameplayStatics::GetPlayerController(GetWorld(), i));
		Cast<ACarController>(gameManager->mPlayerControllers[i])->CreateRaceHUD();

		gameManager->mPlayers.Add(Cast<AAcceleratePlayer>(gameManager->mPlayerControllers[i]->GetPawn()));

		gameManager->mPlayers[i]->CreatePrimaryOffensiveWeapon(gameManager->GetSelectedPrimaryOffensiveWeapons().FindRef(ids[i]));
	}
}

void ABattleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AActor* ABattleManager::ChoosePlayerStart_Implementation(AController* Player)
{
	if (playerStartAssignCode == 0)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), playerStarts);
	}

	return playerStarts[playerStartAssignCode++];
}