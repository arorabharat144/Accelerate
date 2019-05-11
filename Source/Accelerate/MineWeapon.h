// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SecondaryWeapon.h"
#include "MineWeapon.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class AMine;

UCLASS()
class ACCELERATE_API AMineWeapon : public ASecondaryWeapon
{
	GENERATED_BODY()

public:
	AMineWeapon();

protected:
	void BeginPlay() override;

public:
	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Mine")
		void Fire() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* MineMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mine")
		TSubclassOf<AMine> mineRef;

	UPROPERTY(EditAnywhere, Category = "SpawnSpot")
		USceneComponent* Spawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float damage;

};
