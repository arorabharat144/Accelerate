// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SecondaryWeapon.h"
#include "Components/BoxComponent.h"
#include "Hook.generated.h"

/**
 *
 */
UCLASS()
class ACCELERATE_API AHook : public ASecondaryWeapon
{
	GENERATED_BODY()
public:

	AHook();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void Fire() override;

	UFUNCTION()
		void OnComponentOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//DESIGNER TOOLS
	float hookPullSpeed{ 1000.0f };
	float hookPullDuration{ 3.0f };
	float hookTravelSpeed{ 10000.0f };
	FString meshName{ "/Game/Design/EviromentalObjects/ExplodingBarrel/SM_Barrel" };
	float meshScale{ 4.0f };
	//DESIGNER TOOLS

	UStaticMeshComponent* hookMesh;
private:
	void EndHook();

	bool mIsActive{ false };
	UPROPERTY(EditAnywhere)
	UBoxComponent* mHookCollider { nullptr };
	FVector mFireDirection{ 0.0f };
	class AAcceleratePlayer* mHookedPlayer{ nullptr };
	FVector mPlayerLocation;
	FVector mPullDirection;
	FRotator mPlayerRotation;
	FTimerHandle mTimerHandle;
};
