// Fill out your copyright notice in the Description page of Project Settings.

#include "FlameThrower.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "AcceleratePlayer.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"

AFlameThrower::AFlameThrower()
{
	
	//mFlameThrowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlameThrowerMesh"));
	//RootComponent = mFlameThrowerMesh;
	//
	//ConstructorHelpers::FObjectFinder<UParticleSystem> flameThrower(TEXT("/Game/Design/Weapons/BaseWeapons/Offensive/FlameThrower/Particles/ParticleSystem_FlameThrower"));
	//mFlameThrower = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FlameParticleSystem"));
	//
	//mFlameCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("FlameCollider"));
	//mFlameCollider->SetWorldScale3D(FVector(35.0f, 7.0f, 7.0f));
	//mFlameCollider->SetHiddenInGame(true);
	//mFlameCollider->BodyInstance.SetCollisionProfileName(TEXT("OverlapAll"));
	//mFlameCollider->SetNotifyRigidBodyCollision(true);
	//mFlameCollider->OnComponentBeginOverlap.AddDynamic(this, &AFlameThrower::OnOverlapBegin);
	//mFlameCollider->OnComponentEndOverlap.AddDynamic(this, &AFlameThrower::OnOverlapEnd);
	//mFlameCollider->CurrentTag = 5;
	//mFlameCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//
	//if(flameThrower.Succeeded())
	//{
	//	mFlameThrower->SetTemplate(flameThrower.Object);
	//}
	
}

void AFlameThrower::BeginPlay()
{
	Super::BeginPlay();
	//SetActorRelativeLocation(FVector(550.0f, 0.0f, 0.0f));
	//mFlameThrower->SetWorldScale3D(FVector(2.0f));
	//mFlameThrower->AttachToComponent(mFlameThrowerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//mFlameThrower->Deactivate();
}

void AFlameThrower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FVector newColliderLocation = GetActorLocation();
	//newColliderLocation += (GetActorForwardVector() * LocationForward);
	//mFlameCollider->SetWorldLocation(newColliderLocation);
	//
	//if (mIsActive && mCanDamge)
	//{
	//	if (mOverlappedPlayer)
	//	{
	//		mCanDamge = false;
	//		mOverlappedPlayer->ReceiveDamage(damage);
	//		GetWorldTimerManager().SetTimer(mTimerHandle, this, &AFlameThrower::EnableDamage, 1.0f, true, damageCooldown);
	//	}
	//}
}

void AFlameThrower::Fire(float value)
{
	//if (value > 0.0f)
	//{
	//	if (mCurrentHeatLevel < mMaxHeatLevel)
	//	{
	//		//Reduce the heat level of the weapon
	//		IncrementHeatLevel();
	//		mFlameThrower->Activate();
	//		mIsActive = true;
	//	}
	//	else
	//	{
	//		mFlameThrower->Deactivate();
	//		mIsActive = false;
	//	}
	//}
	//else
	//{
	//	DecrementHeatLevel();
	//	mFlameThrower->Deactivate();
	//	mIsActive = false;
	//}	
}

void AFlameThrower::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && OtherActor->IsA(AAcceleratePlayer::StaticClass()))
	{
		mOverlappedPlayer = static_cast<AAcceleratePlayer*>(OtherActor);
	}
}

void AFlameThrower::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != this && OtherActor->IsA(AAcceleratePlayer::StaticClass()))
	{
		mOverlappedPlayer = nullptr;
	}
}

FString AFlameThrower::GetBlueprintPath()
{
	return FString("Blueprint'/Game/BluePrints/BaseWeapons/BP_FlameThrower.BP_FlameThrower'");
}