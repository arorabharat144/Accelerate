// Fill out your copyright notice in the Description page of Project Settings.

#include "Hook.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "AcceleratePlayer.h"

AHook::AHook()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent->SetRelativeLocation(FVector(0.0f));
	mHookCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("HookCollider"));
	mHookCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	mHookCollider->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	mHookCollider->SetHiddenInGame(true);
	mHookCollider->SetRelativeLocation(FVector(0.0f));
	mHookCollider->SetWorldScale3D(FVector(2.0f));
	mHookCollider->SetNotifyRigidBodyCollision(true);
	mHookCollider->BodyInstance.SetCollisionProfileName(TEXT("OverlapAll"));
	mHookCollider->SetGenerateOverlapEvents(true);
	mHookCollider->OnComponentBeginOverlap.AddDynamic(this, &AHook::OnComponentOverlapBegin);
	hookMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HookMesh"));
	hookMesh->AttachToComponent(mHookCollider, FAttachmentTransformRules::KeepRelativeTransform);
	hookMesh->SetRelativeLocation(FVector(0.0f));
	hookMesh->SetWorldScale3D(FVector(meshScale));
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(*meshName);
	if (MeshAsset.Succeeded())
	{
		hookMesh->SetStaticMesh(MeshAsset.Object);
	}
	hookMesh->SetCollisionProfileName(FName("OverlapAll"));

}

void AHook::BeginPlay()
{
	Super::BeginPlay();
}

void AHook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newHookLocation{ 0.0f };
	if (mIsActive)
	{
		newHookLocation = mHookCollider->GetComponentLocation();
		newHookLocation += mFireDirection * hookTravelSpeed * DeltaTime;
		mHookCollider->SetRelativeLocation(newHookLocation);
	}

	if (mHookedPlayer)
	{
		mPlayerLocation -= mPullDirection * hookPullSpeed * DeltaTime;
		mHookedPlayer->SetActorLocation(mPlayerLocation);
		mHookedPlayer->SetActorRotation(mPlayerRotation);
	}
}

void AHook::Fire()
{
	if (mIsActive)//Retract
	{
		mIsActive = false;
		hookMesh->SetHiddenInGame(true);
		mHookedPlayer = nullptr;
		//mHookCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		GetWorldTimerManager().ClearTimer(mTimerHandle);
	}
	else if (GetAmmo() > 0)//Fire
	{
		SetAmmo(GetAmmo() - 1);
		hookMesh->AttachToComponent(mHookCollider, FAttachmentTransformRules::KeepRelativeTransform);
		hookMesh->SetRelativeLocation(FVector(0.0f));
		hookMesh->SetWorldScale3D(FVector(meshScale));
		mIsActive = true;
		hookMesh->SetHiddenInGame(false);
		mFireDirection = RootComponent->GetForwardVector();
		FVector newHookPos = RootComponent->GetComponentLocation();
		mHookCollider->SetWorldRotation(RootComponent->GetComponentRotation());
		newHookPos += mFireDirection * 400.0f;
		mHookCollider->SetWorldLocation(newHookPos);
	}
}

void AHook::OnComponentOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetOwningPlayer() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("EMP ERROR: No Owning player set"));
		return;
	}
	if (OtherActor->IsA(AAcceleratePlayer::StaticClass()) && mIsActive && !Cast<AAcceleratePlayer>(OtherActor)->isShieldActive &&
		GetOwningPlayer()->GetName() != OtherActor->GetName())
	{
		mHookedPlayer = Cast<AAcceleratePlayer>(OtherActor);
		mPlayerLocation = mHookedPlayer->GetActorLocation();
		mPullDirection = mHookedPlayer->GetActorForwardVector();
		mPlayerRotation = mHookedPlayer->GetActorRotation();
		hookMesh->AttachToComponent(mHookedPlayer->Mesh, FAttachmentTransformRules::KeepWorldTransform);
		GetWorldTimerManager().SetTimer(mTimerHandle, this, &AHook::EndHook, hookPullDuration, false);
	}
}

void AHook::EndHook()
{
	hookMesh->SetHiddenInGame(true);
	mIsActive = false; 
	mHookedPlayer = nullptr;
}