// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"

#include "SecondaryWeapon.generated.h"

/**
 *
 */
UCLASS()
class ACCELERATE_API ASecondaryWeapon : public APickup
{
	GENERATED_BODY()

public:
	ASecondaryWeapon();

	virtual void Tick(float DeltaTime);

	virtual void WasCollected_Implementation();

	virtual void Fire();

	virtual void SetIsDoubleDamage(bool isDoubDam);

	//Get the amount of Ammo for this weapon
	UFUNCTION(BlueprintPure, Category = "WeaponPickup")
	int GetAmmo() const;

	//Set the amount of ammo
	UFUNCTION(BlueprintCallable, Category = "WeaponPickup")
	void SetAmmo(int ammo);

	//Get weapon Type
	UFUNCTION(BlueprintPure, Category = "WeaponPickup")
	EPickupTypes GetWeaponType();

	UPROPERTY(EditAnywhere, Category = "WeaponPickup")
	EPickupTypes mWeaponPickupType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponPickup")
	bool mIsDoubleDamage{ false };

	UFUNCTION(BlueprintCallable, Category = "WeaponPickup")
	void SetOwningPlayer(AAcceleratePlayer* player) { mOwningPlayer = player; }

	UFUNCTION(BlueprintCallable, Category = "WeaponPickup")
	AAcceleratePlayer* GetOwningPlayer() const { return mOwningPlayer; }
protected:

	virtual void BeginPlay() override;

private:
	uint32 mAmmo;

	AAcceleratePlayer* mOwningPlayer{ nullptr };
};
