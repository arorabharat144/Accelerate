// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */

UENUM()
enum class EModes : uint8
{
	None,
	Race UMETA(DisplayName = "Race"),
	Battle UMETA(DisplayName = "Battle")
};

class ModeType
{
public:
	struct CarType
	{
		FString model;
		FString color;
	};

	FString map;
};

class RaceModeType : public ModeType
{
public:
	struct RaceCarType : public ModeType::CarType {};

	TArray<RaceCarType> raceCarValues;
};

class BattleModeType : public ModeType
{
public:
	struct BattleCarType : public ModeType::CarType
	{
		FString baseOffensive;
		FString baseDefensive;
	};

	TArray<BattleCarType> battleCarValues;
};