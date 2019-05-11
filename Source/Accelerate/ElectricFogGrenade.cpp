// Fill out your copyright notice in the Description page of Project Settings.

#include "ElectricFogGrenade.h"

// Sets default values
AElectricFogGrenade::AElectricFogGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AElectricFogGrenade::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElectricFogGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

