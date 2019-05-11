// Name : Bharat Arora (Bobby)
// Date : 2nd September 2018
// Description : Homing missile class and implementation for homing missile functionality

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/GameFramework/Pawn.h"
#include "ObjectWithinPool.h"
#include "HomingMissile.generated.h"

UCLASS()
class ACCELERATE_API AHomingMissile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHomingMissile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
