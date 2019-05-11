// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleManager.generated.h"

/**
 * 
 */
UCLASS()
class ACCELERATE_API ABattleManager : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABattleManager();

protected:
	void BeginPlay() override;

public:
	void Tick(float DeltaTime) override;

private:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

private:
	TArray<AActor*> playerStarts;
	uint32 playerStartAssignCode{ 0 };

	TMap<int32, float> mPoints;

	float mTime;
	float mWinningPoints;
	
};
