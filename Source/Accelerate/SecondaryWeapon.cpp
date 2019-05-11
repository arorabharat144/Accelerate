// Fill out your copyright notice in the Description page of Project Settings.

#include "SecondaryWeapon.h"

ASecondaryWeapon::ASecondaryWeapon()
{
	//Constructor
	mPickupType = GetPickupType();

}

void ASecondaryWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASecondaryWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASecondaryWeapon::WasCollected_Implementation()
{
	Super::WasCollected_Implementation();

}

int ASecondaryWeapon::GetAmmo() const
{
	return mAmmo;
}

void ASecondaryWeapon::SetAmmo(int ammo)
{
	mAmmo = ammo;
}

EPickupTypes ASecondaryWeapon::GetWeaponType()
{
	return mWeaponPickupType;
}

void ASecondaryWeapon::Fire()
{
	UE_LOG(LogClass, Log, TEXT("Firing..."));
}

void ASecondaryWeapon::SetIsDoubleDamage(bool isDoubDam)
{
	mIsDoubleDamage = isDoubDam;
}