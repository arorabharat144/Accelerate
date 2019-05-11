// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SecondaryWeapon.h"
#include "RPGMissile.h"
#include "RPGWeapon.generated.h"

UCLASS()
class ACCELERATE_API ARPGWeapon : public ASecondaryWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPGWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Homing Missile")
		void Fire() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* rpgWeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Homing Weapon Projectiles")
		TSubclassOf<ARPGMissile> rpgRef;

	UPROPERTY(EditAnywhere, Category = "Muzzle")
		USceneComponent* muzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float damage;
};
