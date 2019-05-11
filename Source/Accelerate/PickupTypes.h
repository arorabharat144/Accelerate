// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ObjectMacros.h"

UENUM(BlueprintType)
enum class EPickupCategories : uint8
{
	DefensiveWeapon	UMETA(DisplayName = "DefensiveWeapon"),
	OffensiveWeapon	UMETA(DisplayName = "OffensiveWeapon"),
	Boost	UMETA(DisplayName = "Boost"),
	Health	UMETA(DisplayName = "Health"),
	DoubleDamage UMETA(DisplayName = "DoubleDamage"),
	DoublePoints UMETA(DisplayName = "DoublePoints")
};

// Once the Pickup is finished add it to the list.
UENUM(BlueprintType)
enum class EPickupTypes : uint8
{
	none,
	//Utility Pickups
	Boost UMETA(DisplayName = "Boost"),
	Health UMETA(DisplayName = "Health"),
	DoubleDamage UMETA(DisplayName = "DoubleDamage"),
	DoublePoints UMETA(DisplayName = "DoublePoints"),

	//Defensive Pickups
	Mine UMETA(DisplayName = "Mine"),

	// Put new Defense Weapons in this space
	Flash UMETA(DisplayName = "Flash"),
	DomeShield UMETA(DisplayName = "DomeShield"),

	//------------------------------------------------|
	EMP UMETA(DisplayName = "EMP"),

	//Offensive Pickups
	Missile UMETA(DisplayName = "Missile"),
	Drain UMETA(DisplayName = "Drain"),
	// Put new Offensive Weapons in this space
	Phase UMETA(DisplayName = "Phase"),
	RPG UMETA(DisplayName = "RPG"),
	
	//------------------------------------------------|
	Hook UMETA(DisplayName = "Hook")

};