// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/GameFramework/Pawn.h"
#include "Mine.generated.h"

UCLASS()
class ACCELERATE_API AMine : public AActor
{
	GENERATED_BODY()

public:

	AMine();

protected:

	void BeginPlay() override;

public:

	void Tick(float DeltaTime) override;
};
