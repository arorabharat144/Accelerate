// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPool.generated.h"

class AObjectWithinPool;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACCELERATE_API UObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPool();
	AObjectWithinPool* GetObjectInPool();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	void CreateObjects();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, Category = "ObjectPooler")
	TSubclassOf<class AObjectWithinPool> mPooledObjectSubclass;
		
	UPROPERTY(EditAnywhere, Category = "ObjectPooler")
	uint32 mSize = 100;
	
	TArray<AObjectWithinPool*> mPool;
};
