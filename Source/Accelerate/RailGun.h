// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PrimaryWeapon.h"
#include "RailGun.generated.h"

UCLASS()
class ACCELERATE_API ARailGun : public APrimaryWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARailGun();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void Fire(float value) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "PrimaryWeaponFireEvent"), BlueprintCallable)
		void RailGunBlasterFireEvent();

	FString GetBlueprintPath() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RailGunProperties")
		float mMaxCadency{ 0.8f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RailGunProperties")
		float mCurrentCadency{ 0.8f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RailGunProperties")
		float mDamage{ 5.0f };

};
