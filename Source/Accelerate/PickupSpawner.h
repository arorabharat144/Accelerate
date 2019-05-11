// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.h"
#include "PickupTypes.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "PickupSpawner.generated.h"

UCLASS()
class ACCELERATE_API APickupSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickupSpawner();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RandomizePickupTypes();
	void RandomizeAmmo();

	FVector spawnLocation;
	FRotator spawnRotation;
	FActorSpawnParameters spawnParam;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickupType")
		EPickupCategories mPickupCategory = EPickupCategories::DefensiveWeapon;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* SpawnerMesh;
	
	EPickupTypes mPickupType;
	UPROPERTY()
		APickup* mPickup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RefPickup")
		TSubclassOf<class APickup> RefDefensivePickup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RefPickup")
		TSubclassOf<class APickup> RefOffensivePickup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RefPickup")
		TSubclassOf<class APickup> RefBoostPickup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RefPickup")
		TSubclassOf<class APickup> RefHealthPickup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RefPickup")
		TSubclassOf<class APickup> RefDoubleDamagePickup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RefPickup")
		TSubclassOf<class APickup> RefDoublePointsPickup;
	// X is min, Y is max - It will randomize between those two values---|
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponAmmo")
		FVector2D AmmoMine{3.0f,3.0f};
	//Add Defensive Weapons Here-----------------------------------------|
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponAmmo")
	FVector2D AmmoFlash{1.0f,1.0f};
	//-------------------------------------------------------------------|
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponAmmo")
		FVector2D AmmoEMP {3.0f, 3.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponAmmo")
		FVector2D AmmoHomingMissile {3.0f, 3.0f};
	//Add Offensive Weapons Here
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponAmmo")
		FVector2D AmmoPhase {1.0f, 1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponAmmo")
		FVector2D AmmoRPG {3.0f, 3.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponAmmo")
		FVector2D AmmoDrain {1.0f, 1.0f};
	//-------------------------------------------------------------------|
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponAmmo")
		FVector2D AmmoHook {3.0f, 3.0f};

	//Boost Pickup Value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponAmmo")
		float BoostPickupValue {0};
	//Health Pickup Value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponAmmo")
		float HealthPickupValue {0};
	//Boost Pickup Value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duration")
		float DoubleDamageDuration{ 0 };
	//Health Pickup Value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duration")
		float DoublePointsDuration{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickupPosition")
		FVector mPickupPosition = { 0,0,0 };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickupRotation")
		FRotator mPickupRotation = { 0,0,0 };
};
