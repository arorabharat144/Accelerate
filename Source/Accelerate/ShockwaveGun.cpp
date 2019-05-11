// Fill out your copyright notice in the Description page of Project Settings.

#include "ShockwaveGun.h"

AShockwaveGun::AShockwaveGun()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShockwaveGun::BeginPlay()
{
	Super::BeginPlay();
}

void AShockwaveGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShockwaveGun::FireDefensive()
{
	ShockwaveGunFire();
}
