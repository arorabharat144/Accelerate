// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PrimaryWeapon.h"
#include "LaserBlaster.generated.h"

/**
 * 
 */

UCLASS()
class ACCELERATE_API ALaserBlaster : public APrimaryWeapon
{

	GENERATED_BODY()
public:
	ALaserBlaster();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void Fire(float value) override;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "PrimaryWeaponFireEvent"), BlueprintCallable)
	void LaserBlasterFireEvent();

	FString GetBlueprintPath() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaserBlasterProperties")
	float mMaxCadency{ 0.8f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaserBlasterProperties")
	float mCurrentCadency{ 0.8f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaserBlasterProperties")
	float mDamage{ 5.0f };
};
