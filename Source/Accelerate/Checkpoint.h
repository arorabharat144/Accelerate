// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

UENUM()
enum CheckpointType
{
	Start	UMETA(DisplayName = "Start"),
	End		UMETA(DisplayName = "End"),
	Middle	UMETA(DisplayName = "Middle")
};

UCLASS()
class ACCELERATE_API ACheckpoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACheckpoint();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere, Category = "Designer Tools")
		uint32 checkpointNumber {0};

	UPROPERTY(EditAnywhere, Category = "Designer Tools")
		TArray<uint32> nextAICheckpoints;

	void Init();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class UBoxComponent* mCheckpointCollider{ nullptr };


private:
	class ACheckpointManager* mCheckpointManager;
	bool mInit{ false };

};
