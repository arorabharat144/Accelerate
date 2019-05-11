// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PrimaryWeapon.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "vector"
#include "FlameThrower.generated.h"


class AAcceleratePlayer;
class UStaticMeshComponent;

UCLASS()
class ACCELERATE_API AFlameThrower : public APrimaryWeapon
{
	GENERATED_BODY()
public:

	AFlameThrower();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;
	
	void Fire(float value) override;

	void EnableDamage() { mCanDamge = true; }

	FString GetBlueprintPath() override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlameThrowerProperties")
	float damage{ 20 };

	UPROPERTY(EditAnywhere, Category = "FlameThrowerProperties")
	float damageCooldown{ 2.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlameThrowerProperties")
	UParticleSystemComponent* mFlameThrower{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlameThrowerProperties")
	UBoxComponent* mFlameCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrimaryWeapon")
	UStaticMeshComponent* mFlameThrowerMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlameThrowerProperties")
	float LocationForward = 1150.0f;

private:
	bool mIsActive{ false };
	bool mCanDamge{ true };
	AAcceleratePlayer* mOverlappedPlayer;
	FTimerHandle mTimerHandle;
};