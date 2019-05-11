// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PrimaryDefensiveWeapon.h"
#include "BackShield.generated.h"

/**
 * 
 */
UCLASS()
class ACCELERATE_API ABackShield : public APrimaryDefensiveWeapon
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABackShield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireDefensive() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Back Shield")
	void BackShieldFire();

	UFUNCTION(BlueprintCallable, Category = "Back Shield")
	void ReceiveDamage(float damage);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Back Shield Stats")
	float mHealth;

};
