// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Maps.h"
#include "MainMenu.h"
#include "CarCustomizations.h"
#include "ModeTypeContainers.h"

#include "UIStyle.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuManager.generated.h"

class UGameManager;
class AMenuController;
/**
 * 
 */
UCLASS()
class ACCELERATE_API AMainMenuManager : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMainMenuManager();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UMainMenu* GetMainMenu() const;

	bool GetPlayerReadyStatus(uint32 index);
	void SetPlayerReadyStatus(uint32 index, bool status);

	EModes GetSelectedModeEnum() const;

	MyButtonStyle GetButtonStyle(uint32 index) const;
	MyCarCustomizationButtonStyle GetCarCustomizationMenuButtonStyle(uint32 index) const;

	UPROPERTY(EditAnywhere, Category = "Main Menu")
	TSubclassOf<UMainMenu> mainMenuRef;

	UPROPERTY(BlueprintReadOnly, Category = "MainMenu")
	UMainMenu* mMainMenu;

private:

	void CreateMenu();

	void Initialize();

	void InitializeButtonStyles();
	void InitializeCarCustomizationButtonStyles();
	void InitializeCheckBoxesStyles();

	void UpdateButtonStyles();
	void UpdateCarCustomizationButtonStyles();
	void UpdateCheckBoxesStyles();

	UFUNCTION()
	void OnPressedraceModeButton();

	UFUNCTION()
	void OnPressedbattleModeButton();

	UFUNCTION()
	void OnPressedoptionsButton();

	UFUNCTION()
	void OnPressedquitButton();

	UFUNCTION()
	void OnPressedraceBackButton();

	UFUNCTION()
	void OnPressedraceButton();

	UFUNCTION()
	void OnPressedvideoButton();

	UFUNCTION()
	void OnToggleFullscreen(bool isChecked);

	UFUNCTION()
	void OnToggleP1Ready(bool isChecked);

	UFUNCTION()
	void OnToggleP2Ready(bool isChecked);

	UFUNCTION()
	void OnToggleP3Ready(bool isChecked);

	UFUNCTION()
	void OnToggleP4Ready(bool isChecked);

	UFUNCTION()
	void OnPressedaudioButton();

	UFUNCTION()
	void OnPressedoptionsBackButton();

	UFUNCTION()
	void OnPressedyesQuitButton();

	UFUNCTION()
	void OnPressednoQuitButton();

	UFUNCTION()
	void OnPresseddisplayBackButton();

	UFUNCTION()
	void OnPressedaudioBackButton();

	UFUNCTION()
	void OnPressedmapBackButton();

	UFUNCTION()
	void OnPressedmapSpaceButton();

	UFUNCTION()
	void AddAdditionalPlayers();

private:
	UGameManager* mGameManager;

	TArray<MyButtonStyle> mButtonStyles;
	TArray<MyCarCustomizationButtonStyle> mCarCustomizationButtonStyles;
	TArray<MyCheckboxStyle> mCheckboxStyles;

	TArray<bool> mPlayerReadyStatuses;

	EModes mSelectedMode;
};
