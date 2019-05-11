// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SuspensionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACCELERATE_API USuspensionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USuspensionComponent();
	bool CastRay(FHitResult& hit);

	UPROPERTY(Category = "Suspension", EditAnywhere)
	float SuspensionLength = 140.0f;

	UPROPERTY(Category = "Suspension", EditAnywhere)
	float KSuspension = 5000.0f;

	UPROPERTY(Category = "Suspension", EditAnywhere)
	float KDamp = 2.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
