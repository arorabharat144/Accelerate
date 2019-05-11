// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGMissile.h"

// Sets default values
ARPGMissile::ARPGMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARPGMissile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

