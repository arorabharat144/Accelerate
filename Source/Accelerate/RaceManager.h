// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Maps.h"
#include "CarTypes.h"

#include "RaceManager.generated.h"

class ACheckpointManager;
class AAIManager;

/**
 * 
 */
UCLASS()
class ACCELERATE_API ARaceManager : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARaceManager();

protected:
	void BeginPlay() override;

public:
	void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "CheckpointManager")
	TSubclassOf<ACheckpointManager> checkpointManagerRef;

	UPROPERTY(EditAnywhere, Category = "CheckpointManager")
	TMap<EMaps, int> lapCount;

	UPROPERTY(EditAnywhere, Category = "Available Meshes")
	TMap<ECarTypes, UStaticMesh*> availableCarMeshes;

	//Use an #ifdef to check if the build is shipping or not
	UPROPERTY(EditAnywhere, Category = "Debug")
	TArray<ECarTypes> debugCarTypes;

	UPROPERTY(EditAnywhere, Category = "Debug")
	EMaps currentMap;

	UPROPERTY(BlueprintReadOnly)
	ACheckpointManager* checkpointManager;
	
private:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

private:
	TArray<AActor*> playerStarts;
	uint32 playerStartAssignCode{ 0 };
	AAIManager* mAIManager;
};
