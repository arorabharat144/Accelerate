// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PrimaryWeapon.generated.h"


class UStaticMeshComponent;

UCLASS()
class ACCELERATE_API APrimaryWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APrimaryWeapon();

	//Member variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrimaryWeapon")
	float mCurrentHeatLevel {100.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrimaryWeapon")
	float mMaxHeatLevel{100.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrimaryWeapon")
	float mHeatIncrement{2.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrimaryWeapon")
	float mCoolDownDecrement{3.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrimaryWeapon")
	bool mIsDoubleDamage{ false };
	//Functions
	UFUNCTION(BlueprintCallable, Category = "PrimaryWeapon")
	virtual void Fire(float value = 0.0f);

	UFUNCTION(BlueprintCallable, Category = "PrimaryWeapon")
	virtual void IncrementHeatLevel();

	UFUNCTION(BlueprintCallable, Category = "PrimaryWeapon")
	virtual void DecrementHeatLevel();

	UFUNCTION(BlueprintCallable, Category = "PrimaryWeapon")
	virtual void Reload();

	UFUNCTION(BlueprintCallable, Category = "PrimaryWeapon")
	virtual FString GetBlueprintPath() { return FString(""); }
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
