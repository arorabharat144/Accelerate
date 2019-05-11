// Fill out your copyright notice in the Description page of Project Settings.

#include "PrimaryDefensiveWeapon.h"
#include "Engine/Classes/Engine/World.h"

// Sets default values
APrimaryDefensiveWeapon::APrimaryDefensiveWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//why are you doing this Erick=========================Alejandro
	currentCooldown = maxCooldown;

	mCanShoot = true;
	mIsActive = false;

}

// Called when the game starts or when spawned
void APrimaryDefensiveWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APrimaryDefensiveWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CoolDownRecharge();

}

void APrimaryDefensiveWeapon::CoolDownRecharge()
{
	if (mCanShoot == false && mIsActive == false)
	{
		currentCooldown += GetWorld()->GetDeltaSeconds();
		if (currentCooldown >= maxCooldown)
		{
			currentCooldown = maxCooldown;
			mCanShoot = true;
		}
	}
}

void APrimaryDefensiveWeapon::FireDefensive()
{
	UE_LOG(LogClass, Log, TEXT("Firing Defensive Weapon..."));
}

void APrimaryDefensiveWeapon::SetCanShoot(bool canShoot)
{
	mCanShoot = canShoot;
}

void APrimaryDefensiveWeapon::SetIsActive(bool isactive)
{
	mIsActive = isactive;
}

bool APrimaryDefensiveWeapon::GetCanShoot()
{
	return mCanShoot;
}

bool APrimaryDefensiveWeapon::GetIsActive()
{
	return mIsActive;
}