// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PrimaryDefensiveWeapon.h"

#include "ElectricFogGrenade.h"

#include "ElectricFog.generated.h"


/**
 * 
 */
UCLASS()
class ACCELERATE_API AElectricFog : public APrimaryDefensiveWeapon
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AElectricFog();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireDefensive() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Electric Fog")
	void ElectricFogFire();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ElectricFogDamage")
	float mFogDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ElectricFogDamage")
	float mFogDuration;

};
