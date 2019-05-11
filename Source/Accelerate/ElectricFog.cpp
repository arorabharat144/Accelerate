// Fill out your copyright notice in the Description page of Project Settings.

#include "ElectricFog.h"

AElectricFog::AElectricFog()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AElectricFog::BeginPlay()
{
	Super::BeginPlay();
}

void AElectricFog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AElectricFog::FireDefensive()
{
	ElectricFogFire();
}
