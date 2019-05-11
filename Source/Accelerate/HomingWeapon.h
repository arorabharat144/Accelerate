// Name : Bharat Arora (Bobby)
// Date : 2nd September 2018
// Description : Homing weapon class and implementation for homing weapon functionality

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SecondaryWeapon.h"
#include "HomingWeapon.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class AHomingMissile;
class AObjectsSpawner;

UCLASS()
class ACCELERATE_API AHomingWeapon : public ASecondaryWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHomingWeapon();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Homing Missile")
	void Fire() override;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	//UBoxComponent* collisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* homingWeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Homing Weapon Projectiles")
		AObjectsSpawner* missileSpawner;

	UPROPERTY(EditDefaultsOnly, Category = "Homing Weapon Projectiles")
		TSubclassOf<AHomingMissile> missileRef;

	UPROPERTY(EditAnywhere, Category = "Muzzle")
		USceneComponent* muzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homing Weapon Damage")
		float damage;
};
