// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "AICheckpoint.generated.h"

const float VALUE_TO_SPEED[4]{ 0.25f, 0.5f, 0.75f, 1.0f };

UENUM()
enum class SpeedValues
{
	Slow	UMETA(DisplayName = "Slow"),
	Medium	UMETA(DisplayName = "Medium"),
	Fast	UMETA(DisplayName = "Fast"),
	Max		UMETA(DisplayName = "Max"),
};

UENUM()
enum class TurnValues
{
	Slow	UMETA(DisplayName = "Slow"),
	Medium	UMETA(DisplayName = "Medium"),
	Fast	UMETA(DisplayName = "Fast"),
	Max		UMETA(DisplayName = "Max")
};

UCLASS()
class ACCELERATE_API AAICheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAICheckpoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Tools")
	int pathNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Tools")
	int orderNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Tools")
	SpeedValues speedValue{ SpeedValues::Max };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Tools")
	TurnValues turnValue { TurnValues::Max };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Tools")
	bool boost{ false };

private:
	USphereComponent* mSphereComponent;
};
