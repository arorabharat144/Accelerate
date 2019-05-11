// Fill out your copyright notice in the Description page of Project Settings.

#include "DomeShield.h"

// Sets default values
ADomeShield::ADomeShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADomeShield::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADomeShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADomeShield::Fire()
{
	DomeShieldFire();
}

