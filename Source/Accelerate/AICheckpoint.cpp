// Fill out your copyright notice in the Description page of Project Settings.

#include "AICheckpoint.h"

// Sets default values
AAICheckpoint::AAICheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Root"));
	mSphereComponent->SetHiddenInGame(true);
	mSphereComponent->SetSphereRadius(50.0f);
}

// Called when the game starts or when spawned
void AAICheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

