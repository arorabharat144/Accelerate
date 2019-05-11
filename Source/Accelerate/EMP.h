// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SecondaryWeapon.h"
#include "Components/SphereComponent.h"
#include "EMP.generated.h"

/**
 *
 */
UCLASS()
class ACCELERATE_API AEMP : public ASecondaryWeapon
{
	GENERATED_BODY()

public:
	AEMP();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void Fire() override;

	//DESIGNER TOOLS
	float EMP_Radius{ 10000.0f };
	float EMP_Duration{ 10.0f };
	bool show_EMP{ false };
	//DESIGNER TOOLS

	UFUNCTION()
		void OnComponentOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	void EndEMP();

	TArray<AAcceleratePlayer*> mAffectedPlayers;
	TArray<AAcceleratePlayer*> mOverlappedPlayers;
	USphereComponent* mEMPCollider;
};
