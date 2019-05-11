// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleAI.h"
#include "EngineUtils.h"
#include "AcceleratePlayer.h"
#include "PrimaryWeapon.h"
#include "SecondaryWeapon.h"
#include "HomingMissile.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABattleAI::ABattleAI()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = mesh;
}

// Called when the game starts or when spawned
void ABattleAI::BeginPlay()
{
	Super::BeginPlay();

	mesh->SetSimulatePhysics(true);
	mesh->SetEnableGravity(true);

	mHealth = startingHealth;
}

// Called every frame
void ABattleAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	mDeltaTime = DeltaTime;

	// Initialize by setting the AIManager to its instance and initializing the first checkpoint.
	if (!mInit)
	{
		Init();
		mInit = true;
	}

	if (mFireWeaponIntervalTimer < fireWeaponIntervalTime)
	{
		mFireWeaponIntervalTimer += mDeltaTime;
	}
	if (mAttentionTimer < attentionSpan)
	{
		mAttentionTimer += mDeltaTime;
	}

	if (mHealth <= 0.0f)
	{
		mHealth = startingHealth;
		SetActorLocation(mRespawnLocation);
		mCurrentState = BattleAIStates::Patrol;
	}


	//If AIManager is not found, the program will do nothing
	if (mAIManager)
	{
		mLocation = GetActorLocation();

		//Set mCurrentTarget if AIManager finds any targets within a certain height (Z)
		if (!mCurrentTarget)
		{
			mCurrentTarget = mAIManager->GetTarget(mLocation, targetHeightDifference);
			mAttentionTimer = 0.0f;
			mFireWeaponIntervalTimer = fireWeaponIntervalTime;
		}

		if (mCurrentTarget)
		{
			mCurrentState = BattleAIStates::Attack;
		}
		else
		{
			mCurrentState = BattleAIStates::Patrol;
		}

		switch (mCurrentState)
		{
		case BattleAIStates::Patrol:
			Patrol();
			break;
		case BattleAIStates::Attack:
			Attack();
			break;
		default:
			break;
		}
	}
}

void ABattleAI::Init()
{
	for (TActorIterator<AAIManager> controller(GetWorld()); controller; ++controller)
	{
		mAIManager = *controller;
	}

	mCurrentCheckpoint = mAIManager->GetCheckpoint(pathNumber, 0);
	mRespawnLocation = mCurrentCheckpoint->GetActorLocation();

	FActorSpawnParameters params;
	params.Owner = this;
	mWeapon = GetWorld()->SpawnActor<ALaserBlaster>(laserBlasterRef->GetAuthoritativeClass(), params);
	FAttachmentTransformRules rules{ EAttachmentRule::SnapToTarget, true };
	mWeapon->AttachToComponent(mesh, rules, TEXT("SK_PrimaryWeapon"));
}

void ABattleAI::Patrol()
{
	mCurrentCheckpoint = mAIManager->BattleUpdate(mCurrentCheckpoint, mLocation, mIterate);



	FRotator newRotation;
	FQuat quatRotation;
	switch (mAIManager->GetAction(GetActorForwardVector(), mLocation, mCurrentCheckpoint->GetActorLocation()))
	{
	case AIPlayerActions::Left:
		newRotation = FRotator(0.0f, -rotateSpeed * mDeltaTime, 0.0f);
		quatRotation = FQuat(newRotation);
		AddActorLocalRotation(quatRotation, false, nullptr, ETeleportType::None);
		break;
	case AIPlayerActions::Right:
		newRotation = FRotator(0.0f, rotateSpeed * mDeltaTime, 0.0f);
		quatRotation = FQuat(newRotation);
		AddActorLocalRotation(quatRotation, false, nullptr, ETeleportType::None);
		break;
	default:
		break;
	}

	FVector forward = GetActorForwardVector();
	forward.Normalize();
	mLocation += forward * travelSpeed * mDeltaTime;
	SetActorLocation(mLocation);
}


void ABattleAI::Attack()
{
	if (mCurrentTarget && (abs(mCurrentTarget->GetActorLocation().Z - mLocation.Z) <= targetHeightDifference))
	{
		FRotator newRotation;
		FQuat quatRotation;
		switch (mAIManager->GetAction(GetActorForwardVector(), mLocation, mCurrentTarget->GetActorLocation()))
		{
		case AIPlayerActions::Left:
			newRotation = FRotator(0.0f, -rotateSpeed * 2.0f * mDeltaTime, 0.0f);
			quatRotation = FQuat(newRotation);
			AddActorLocalRotation(quatRotation, false, nullptr, ETeleportType::None);
			break;
		case AIPlayerActions::Right:
			newRotation = FRotator(0.0f, rotateSpeed * 2.0f * mDeltaTime, 0.0f);
			quatRotation = FQuat(newRotation);
			AddActorLocalRotation(quatRotation, false, nullptr, ETeleportType::None);
			break;
		default:
			break;
		}


		if (mFireWeaponIntervalTimer >= fireWeaponIntervalTime)
		{
			mWeapon->Fire(1.0f);
			mFireWeaponIntervalTimer = 0.0f;
		}

		
		if (mAttentionTimer >= attentionSpan)
		{
			mCurrentState = BattleAIStates::Patrol;
			mCurrentTarget = nullptr;
		}


	}
	else
	{
		mCurrentState = BattleAIStates::Patrol;
		mCurrentTarget = nullptr;
	}
}
