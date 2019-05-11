// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SecondaryWeapon.h"
#include "FlashWeapon.generated.h"

/**
 * 
 */
UCLASS()
class ACCELERATE_API AFlashWeapon : public ASecondaryWeapon
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AFlashWeapon();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Flash Weapon")
		void Fire() override;
};
