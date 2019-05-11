// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PrimaryDefensiveWeapon.h"
#include "ShockwaveGun.generated.h"

/**
 * 
 */
UCLASS()
class ACCELERATE_API AShockwaveGun : public APrimaryDefensiveWeapon
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AShockwaveGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireDefensive() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Shockwave Gun ")
	void ShockwaveGunFire();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shockwave Gun Stats")
	bool mIsReady;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shockwave Gun Stats")
	float mCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shockwave Gun Stats")
	float mRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shockwave Gun Stats")
	float mGrowTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shockwave Gun Stats")
	FVector mPushForceVetor;

};
