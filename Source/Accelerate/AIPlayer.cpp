// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPlayer.h"
#include "EngineUtils.h"
#include "AICheckpoint.h"
#include "AIManager.h"

AAIPlayer::AAIPlayer()
{


}

void AAIPlayer::BeginPlay()
{
	Super::BeginPlay();

}

void AAIPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	
	if (!mInit)
	{
		Init();
		mInit = true;
	}
	
	mCurrentCheckpoint = mAIManager->RaceUpdate(GetActorLocation(), mCurrentCheckpoint);
	mIdleTimer += DeltaTime;
	
	if (mIdleTimer >= (idleRespawnTime * 0.5f) && !mLastLocationSet)
	{
		mLastLocation = GetActorLocation();
		mLastLocationSet = true;
	}
	else if (mIdleTimer >= idleRespawnTime)
	{
		if (FVector::DistSquared(mLastLocation, GetActorLocation()) <
			(idlePassDistance * idlePassDistance))
		{
			Health = 0.0f;
		}
		mIdleTimer = 0.0f;
		mLastLocationSet = false;
	}
	
	if (mCurrentCheckpoint->boost)
	{
		ACar::Boost();
	}
	
	Accelerate(VALUE_TO_SPEED[static_cast<int>(mCurrentCheckpoint->speedValue)]);
	AIPlayerActions action = mAIManager->GetAction(GetActorForwardVector(), GetActorLocation(),
		mCurrentCheckpoint->GetActorLocation());
	
	if (action == AIPlayerActions::Left)
	{
		Turn(-VALUE_TO_SPEED[static_cast<int>(mCurrentCheckpoint->turnValue)]);
	}
	else if (action == AIPlayerActions::Right)
	{
		Turn(VALUE_TO_SPEED[static_cast<int>(mCurrentCheckpoint->turnValue)]);
	}
}

void AAIPlayer::SetCurrentCheckpoint(uint32 checkpoint)
{
	if (mAIManager)
	{
		mCurrentCheckpoint = mAIManager->GetCheckpoint(pathNumber, checkpoint);
	}
}

void AAIPlayer::Init()
{
	for (TActorIterator<AAIManager> controller(GetWorld()); controller; ++controller)
	{
		mAIManager = *controller;
	}
	if (!mAIManager)
	{
		throw;
	}
	mCurrentCheckpoint = mAIManager->GetCheckpoint(pathNumber, startingCheckpoint);
}
