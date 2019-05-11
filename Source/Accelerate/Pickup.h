// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PickupTypes.h"
#include "Pickup.generated.h"

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetEnumName((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

class UBoxComponent;
class UStaticMeshComponent;
class AAcceleratePlayer;

UCLASS()
class ACCELERATE_API APickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickup();

	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool PickupState);

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void ResetPickup();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void EndOfDuration();

	UFUNCTION(BlueprintPure, Category = "Pickup")
	EPickupTypes GetPickupType() const;

	//What happen when the pickup was collected_Callable on Blueprints
	UFUNCTION(BlueprintNativeEvent)
	void WasCollected();

	//Code to be override in children classes
	virtual void WasCollected_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FTimerHandle timerHandle;
	FTimerHandle durationTimerHandle;
	
	void RandomizePickupTypes();

	// It's true when the pickup can be used, and false when pickup is deactivated
	bool mIsActive;

public:

	//This will be in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnTime")
	float SpwanTime = 2;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickupCollider")
	class UBoxComponent* mPickupCollider;

	AAcceleratePlayer* mOverlappedPlayer;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float Ammo{0.0f};
	float Boost{ 0.0f };
	float Health{ 0.0f };
	float DoublePointsDuration{ 0.0f };
	float DoubleDamageDuration{ 0.0f };

	//TODO: Make this a private but still accesable 
	//Static mesh component for pickup (This is the Current Static Mesh For the Pickup)	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mPickupMesh;

	//UPROPERTY(EditAnywhere, Category = "Pickup")
	EPickupTypes mPickupType;

	EPickupCategories mPickupCategory;
};
