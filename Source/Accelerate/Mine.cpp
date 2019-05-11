// Fill out your copyright notice in the Description page of Project Settings.

#include "Mine.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/AudioComponent.h"
#include "Runtime/Engine/Classes/Sound/SoundCue.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Runtime/Engine/Classes/PhysicsEngine/RadialForceComponent.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

#include "AcceleratePlayer.h"


AMine::AMine()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMine::BeginPlay()
{
	Super::BeginPlay();
}

void AMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}