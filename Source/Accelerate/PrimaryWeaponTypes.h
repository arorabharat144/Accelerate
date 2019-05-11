// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ObjectMacros.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class EPrimaryOffensiveWeaponTypes : uint8
{
	None	        UMETA(DisplayName = "None"),
	LaserBlaster	UMETA(DisplayName = "LaserBlaster"),
	Flamethrower	UMETA(DisplayName = "Flamethrower"),
	Railgun     	UMETA(DisplayName = "Railgun")
};

UENUM(BlueprintType)
enum class EPrimaryDefensiveItemTypes : uint8
{
	None	        UMETA(DisplayName = "None"),
	BackShield		UMETA(DisplayName = "BackShield"),
	ShockWave		UMETA(DisplayName = "ShockWave"),
	ElectricFog    	UMETA(DisplayName = "ElectricFog")
};
