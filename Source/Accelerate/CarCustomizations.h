// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ObjectMacros.h"

/**
 *
 */
UENUM(BlueprintType)
enum class ECarCustomizations : uint8
{
	Model UMETA(DisplayName = "Model"),
	Color UMETA(DisplayName = "Color"),
	BaseOffense UMETA(DisplayName = "BaseOffense"),
	BaseDefense UMETA(DisplayName = "BaseDefense")
};
