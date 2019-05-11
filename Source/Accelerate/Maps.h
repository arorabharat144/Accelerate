// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ObjectMacros.h"

UENUM(BlueprintType)
enum class EMaps : uint8
{
	None,
	MainMenu UMETA(DisplayName = "MainMenu"),
	CyberCity UMETA(DisplayName = "CyberCity"),
	NoWayFreeway UMETA(DisplayName = "NoWayFreeway"),
	BattleDome UMETA(DisplayName = "BattleDome")
};
