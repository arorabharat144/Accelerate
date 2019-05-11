// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIManager.h"
#include "Components/StaticMeshComponent.h"
#include "AICheckpoint.h"
#include "BattleAI.generated.h"

class AAcceleratePlayer;
class APrimaryWeapon;
class ASecondaryWeapon;

UCLASS()
class ACCELERATE_API ABattleAI : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABattleAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init();

	void Patrol();
	void Attack();

	UPROPERTY(EditAnywhere, Category = "BattleAI Properties")
		UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, Category = "BattleAI Properties")
		int pathNumber{ 0 };

	UPROPERTY(EditAnywhere, Category = "BattleAI Properties")
		int points{ 15 };

	UPROPERTY(EditAnywhere, Category = "BattleAI Properties")
		int startingHealth{ 50 };

	UPROPERTY(EditAnywhere, Category = "BattleAI Properties")
		float travelSpeed{ 3000.0f };

	UPROPERTY(EditAnywhere, Category = "BattleAI Properties")
		float rotateSpeed{ 100.0f };

	UPROPERTY(EditAnywhere, Category = "BattleAI Properties")
		float targetHeightDifference{ 300.0f };

	UPROPERTY(EditAnywhere, Category = "BattleAI Properties")
		float fireWeaponIntervalTime{ 2.0f };

	UPROPERTY(EditAnywhere, Category = "BattleAI Properties")
		float attentionSpan{ 5.0f };

	//Secondary Weapons refs
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ALaserBlaster> laserBlasterRef;

	float& GetHealth() { return mHealth; }
private:
	float mDeltaTime;
	FVector mLocation;
	FVector mRespawnLocation;
	AAICheckpoint* mCurrentCheckpoint;
	BattleAIStates mCurrentState{ BattleAIStates::Patrol };
	int mIterate{ 1 };
	float mHealth;
	AAcceleratePlayer* mCurrentTarget{ nullptr };
	APrimaryWeapon* mWeapon{ nullptr };
	float mFireWeaponIntervalTimer{ 0.0f };
	float mAttentionTimer{ 0.0f };

	bool mInit{ false };
	AAIManager* mAIManager{ nullptr };
};
