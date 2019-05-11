// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElectricFogGrenade.generated.h"

UCLASS()
class ACCELERATE_API AElectricFogGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElectricFogGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ElectricFogGrenade")
	float mFogDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ElectricFogGrenade")
	float mFogDamage;

};
