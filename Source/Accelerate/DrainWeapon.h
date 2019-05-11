// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma once

#include "CoreMinimal.h"
#include "SecondaryWeapon.h"
#include "DrainWeapon.generated.h"

/**
 *
 */
class ADrain;

UCLASS()
class ACCELERATE_API ADrainWeapon : public ASecondaryWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADrainWeapon();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Homing Missile")
		void Fire() override;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	//UBoxComponent* collisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* DrainWeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Beam")
		TSubclassOf<ADrain> drainRef;

	UPROPERTY(EditAnywhere, Category = "Spawn")
		USceneComponent* Spawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float damage;
};
