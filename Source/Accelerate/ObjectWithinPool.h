// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectWithinPool.generated.h"

UCLASS()
class ACCELERATE_API AObjectWithinPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectWithinPool();

	virtual void SetLifeSpan(float InLifeSpan) override;
	UFUNCTION(BlueprintCallable)
	void SetActive(bool isActive);

	UFUNCTION(BlueprintCallable)
	bool IsActive() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Object")
	AActor* mObject;

private:
	float mLifeSpan{ 10.0f };
	FTimerHandle mLifeSpanTimer;
	bool mISActive;

	void Deactivate();
	
	
};
