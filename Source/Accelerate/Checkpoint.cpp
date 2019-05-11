// Fill out your copyright notice in the Description page of Project Settings.

#include "Checkpoint.h"
#include "Components/BoxComponent.h"
#include "AcceleratePlayer.h"
#include "AIPlayer.h"
#include "EngineUtils.h"
#include "Components/StaticMeshComponent.h"
#include "CheckpointManager.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	mCheckpointCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckpointCollider"));
	mCheckpointCollider->SetupAttachment(RootComponent);
	mCheckpointCollider->BodyInstance.SetCollisionProfileName(TEXT("Custom"));
	mCheckpointCollider->SetNotifyRigidBodyCollision(true);
	mCheckpointCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
	mCheckpointCollider->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);
	mCheckpointCollider->SetWorldScale3D(FVector(5.0f, 80.0f, 5.0f));
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!mInit)
	{
		Init();
		mInit = true;
		PrimaryActorTick.bCanEverTick = false;
	}
}

void ACheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AAcceleratePlayer::StaticClass()) &&
		OtherComp->IsA(UStaticMeshComponent::StaticClass()))
	{
		AAcceleratePlayer* player = Cast<AAcceleratePlayer>(OtherActor);
		mCheckpointManager->SetCheckpoint(player, this);
	}
}

void ACheckpoint::Init()
{
	for (TActorIterator<ACheckpointManager> checkpointManager(GetWorld());
		checkpointManager; ++checkpointManager)
	{
		mCheckpointManager = *checkpointManager;
	}
}
