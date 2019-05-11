// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "PrimaryWeaponTypes.h"

#include "MenuController.generated.h"

class UGameManager;
class AMainMenuManager;

/**
 * 
 */
UCLASS()
class ACCELERATE_API AMenuController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMenuController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialize();

	void HideMainMenu();

	EPrimaryOffensiveWeaponTypes GetSelectedPrimaryWeapon() const;
	int32 GetID() const;

	UFUNCTION()
	void ChooseLaserBlaster();

	UFUNCTION()
	void ChooseFlamethrower();

	UFUNCTION()
	void ChooseRailgun();

	UFUNCTION()
	void OnPressedJoinGameKey();

	UFUNCTION()
	void OnPressedstart();

private:

	void SetID();

	UFUNCTION()
	void OnPressedLeftKey();

	UFUNCTION()
	void OnPressedRightKey();

	UFUNCTION()
	void OnPressedBackKey();

private:
	EPrimaryOffensiveWeaponTypes mSelectedPrimaryWeapon{ EPrimaryOffensiveWeaponTypes::None };

	UGameManager* mGameManager;
	AMainMenuManager* mMainMenuManager;

	int32 mID;

};
