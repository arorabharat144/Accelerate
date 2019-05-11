#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/GameFramework/Pawn.h"
#include "RPGMissile.generated.h"

UCLASS()
class ACCELERATE_API ARPGMissile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARPGMissile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};