// Fill out your copyright notice in the Description page of Project Settings.

#include "BackShield.h"

ABackShield::ABackShield()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABackShield::BeginPlay()
{
	Super::BeginPlay();
}

void ABackShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABackShield::FireDefensive()
{
	BackShieldFire();
}

void ABackShield::ReceiveDamage(float damage)
{
	
	mHealth -= damage;
	if (mHealth < 0.0f)
	{
		mHealth = 0.0f;
	}

}