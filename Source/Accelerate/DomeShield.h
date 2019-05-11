// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SecondaryWeapon.h"

#include "DomeShield.generated.h"

UCLASS()
class ACCELERATE_API ADomeShield : public ASecondaryWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADomeShield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dome Shield")
	void DomeShieldFire();

	//void Fire_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DomeShieldStats")
	bool isReady;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DomeShieldStats")
	bool isDomeShieldActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DomeShieldStats")
	float shieldDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DomeShieldStats")
	float cooldown;

};
