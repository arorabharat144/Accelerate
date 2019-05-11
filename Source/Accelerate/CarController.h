// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "PauseMenu.h"
#include "UIStyle.h"

#include "CarController.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class ACCELERATE_API ACarController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACarController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateRaceHUD();

	void CreateBattleHUD();

	void CreatePauseMenu();

	void InitializePauseMenu();
	void UpdatePauseMenu(float deltaTime);
	
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> raceHudRef;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> battleHudRef;

	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	UUserWidget* mHud;

	UPROPERTY(EditAnywhere, Category = "PauseMenu")
	TSubclassOf<UPauseMenu> pauseMenuRef;

	UPROPERTY(BlueprintReadOnly, Category = "PauseMenu")
	UPauseMenu* mPauseMenu;

private:

	UFUNCTION()
	void OnPressedPause();

	UFUNCTION()
	void OnPressedUnpause();

	UFUNCTION()
	void OnPressedRestart();

	UFUNCTION()
	void OnPressedYesRestart();

	UFUNCTION()
	void OnPressedNoRestart();

	UFUNCTION()
	void OnPressedMainMenu();

	UFUNCTION()
	void OnPressedYesMainMenu();

	UFUNCTION()
	void OnPressedNoMainMenu();

private:
	TArray<MyButtonStyle> mButtonStyles;

	ACarController* mPauseController{ nullptr };
	bool hasOpenedRestartConfirmationScreen{ false };
	bool hasOpenedMainMenuConfirmationScreen{ false };
};
