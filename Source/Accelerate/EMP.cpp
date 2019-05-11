// Fill out your copyright notice in the Description page of Project Settings.

#include "EMP.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Components/SphereComponent.h"
#include "AcceleratePlayer.h"

AEMP::AEMP()
{
	mEMPCollider = CreateDefaultSubobject<USphereComponent>(TEXT("EMP Collider"));
	mEMPCollider->AttachTo(RootComponent);
	mEMPCollider->SetRelativeLocation(FVector(0.0f));
	mEMPCollider->SetSphereRadius(EMP_Radius);
	if (show_EMP)
	{
		mEMPCollider->SetHiddenInGame(false);
	}
	else
	{
		mEMPCollider->SetHiddenInGame(true);
	}
	mEMPCollider->SetNotifyRigidBodyCollision(true);
	mEMPCollider->SetGenerateOverlapEvents(true);
	mEMPCollider->SetCollisionProfileName(FName("OverlapAll"));
	mEMPCollider->OnComponentBeginOverlap.AddDynamic(this, &AEMP::OnComponentOverlapBegin);
	mEMPCollider->OnComponentEndOverlap.AddDynamic(this, &AEMP::OnComponentOverlapEnd);
}

void AEMP::BeginPlay()
{
	Super::BeginPlay();
}

void AEMP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEMP::Fire()
{
	if (GetAmmo() > 0)
	{
		SetAmmo(GetAmmo() - 1);
		EndEMP();
		for (auto player : mOverlappedPlayers)
		{
			if (!player->isShieldActive)
			{
				player->canUseWeapons = false;
			}
		}
		mAffectedPlayers = mOverlappedPlayers;
		FTimerHandle timerHandle;
		GetWorldTimerManager().SetTimer(timerHandle, this, &AEMP::EndEMP, EMP_Duration, false);
	}
}

void AEMP::EndEMP()
{
	for (auto player : mAffectedPlayers)
	{
		player->canUseWeapons = true;
	}
}

void AEMP::OnComponentOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetOwningPlayer() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("EMP ERROR: No Owning player set"));
		return;
	}
	if (OtherActor->IsA(AAcceleratePlayer::StaticClass()) && OtherActor->GetName() != GetOwningPlayer()->GetName())
	{
		mOverlappedPlayers.Push(Cast<AAcceleratePlayer>(OtherActor));
	}
}

void AEMP::OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GetOwningPlayer() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("EMP ERROR: No Owning player set"));
		return;
	}
	if (OtherActor->IsA(AAcceleratePlayer::StaticClass()) && OtherActor->GetName() != GetOwningPlayer()->GetName())
	{
		mOverlappedPlayers.Remove(Cast<AAcceleratePlayer>(OtherActor));
	}
}
