// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ObjectMacros.h"

UENUM(BlueprintType)
enum class ECarTypes : uint8
{
	None,
	Landship UMETA(DisplayName = "Landship"),
	Mawler UMETA(DisplayName = "Mawler"),
	Prowler UMETA(DisplayName = "Prowler"),
	Mantis UMETA(DisplayName = "Mantis")
};
