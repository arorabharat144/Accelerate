// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/CheckBox.h"
#include "Runtime/UMG/Public/Components/CanvasPanel.h"
#include "Runtime/UMG/Public/Components/Border.h"
#include "Runtime/UMG/Public/Components/HorizontalBox.h"
#include "Runtime/UMG/Public/Components/Slider.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

#include "CarCustomizations.h"

#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class ACCELERATE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//virtual void NativeConstruct() override;

	//virtual bool Initialize() override;

	struct CarCustomizationButton
	{
		UButton* left;
		UButton* right;
	};

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Menu")
	void IncreaseOrDecreaseValue(int player, bool isIncrementing, ECarCustomizations variables);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Menu")
	void NextMap();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Menu")
	void PreviousMap();

	TArray<UButton*> GetButtons() const;
	TArray<UCheckBox*> GetCheckBoxes() const;
	TArray<CarCustomizationButton> GetCarCustomizationMenuButtons() const;
public:
	UCanvasPanel* root;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu")
	UVerticalBox* menu;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu")
	UButton* raceModeButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu")
	UButton* battleModeButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu")
	UButton* optionsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu")
	UButton* quitButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu")
	UButton* raceBackButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UVerticalBox* carCustomizationMenu;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UVerticalBox* P1Active;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UVerticalBox* P1InActive;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UTextBlock* p1ModelText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p1MLeftArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p1MRightArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UTextBlock* p1ColorText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p1CLeftArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p1CRightArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UTextBlock* p1BOText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p1BOLeftArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p1BORightArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UTextBlock* p1BDText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UHorizontalBox* p1BaseOffenseWeaponSelection;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UHorizontalBox* p1BaseDefenseWeaponSelection;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p1BDLeftArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p1BDRightArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UCheckBox* p1Ready;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UVerticalBox* P2Active;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UVerticalBox* P2InActive;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P2")
	UTextBlock* p2ModelText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p2MLeftArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p2MRightArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P2")
	UTextBlock* p2ColorText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p2CLeftArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p2CRightArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P2")
	UTextBlock* p2BOText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p2BOLeftArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p2BORightArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P2")
	UTextBlock* p2BDText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UHorizontalBox* p2BaseOffenseWeaponSelection;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UHorizontalBox* p2BaseDefenseWeaponSelection;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p2BDLeftArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p2BDRightArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P2")
	UCheckBox* p2Ready;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UVerticalBox* P3Active;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UVerticalBox* P3InActive;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P3")
	UTextBlock* p3ModelText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p3MLeftArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p3MRightArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P3")
	UTextBlock* p3ColorText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p3CLeftArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p3CRightArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P3")
	UTextBlock* p3BOText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p3BOLeftArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p3BORightArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P3")
	UTextBlock* p3BDText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UHorizontalBox* p3BaseOffenseWeaponSelection;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UHorizontalBox* p3BaseDefenseWeaponSelection;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p3BDLeftArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p3BDRightArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P3")
	UCheckBox* p3Ready;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UVerticalBox* P4Active;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UVerticalBox* P4InActive;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P4")
	UTextBlock* p4ModelText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p4MLeftArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p4MRightArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P4")
	UTextBlock* p4ColorText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p4CLeftArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p4CRightArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P4")
	UTextBlock* p4BOText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p4BOLeftArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p4BORightArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P4")
	UTextBlock* p4BDText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UHorizontalBox* p4BaseOffenseWeaponSelection;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UHorizontalBox* p4BaseDefenseWeaponSelection;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p4BDLeftArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P1")
	UButton* p4BDRightArrow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization P4")
	UCheckBox* p4Ready;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization")
	UButton* raceButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization")
	UImage* unlitRace;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CarCustomization")
	UImage* unlitBattle;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Options")
	UVerticalBox* optionsMenu;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Options")
	UButton* videoButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Options")
	UButton* audioButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Options")
	UButton* optionsBackButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Quit")
	UVerticalBox* quitMenu;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Quit")
	UButton* yesQuitButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Quit")
	UButton* noQuitButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Video")
	UVerticalBox* videoMenu;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Video")
	UButton* displayBackButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Video")
	UCheckBox* fullScreenCheckBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Video")
	USlider* brightnessSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Video")
	USlider* textureQualitySlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Audio")
	UVerticalBox* audioMenu;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Audio")
	UButton* audioBackButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Audio")
	USlider* masterVolumeSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Audio")
	USlider* musicVolumeSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Audio")
	USlider* sfxVolumeSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "RaceMapSelection")
	UCanvasPanel* raceMapSelectionPanel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "RaceMapSelection")
	UButton* mapBackButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "RaceMapSelection")
	UButton* mapSpaceButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "RaceMapSelection")
	UTextBlock* currentRaceTrackText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "BattleMapSelection")
	UCanvasPanel* battleMapSelectionPanel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "RaceMapSelection")
	UTextBlock* currentBattleTrackText;

	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu")
	//UVerticalBox* menu;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu")
	//UImage* mainMenuBackgroundImage;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Player")
	//UButton* twoPlayerButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Player")
	//UButton* threePlayerButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Player")
	//UButton* fourPlayerButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Audio")
	//UButton* audioButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Audio")
	//UButton* audioBackButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Audio")
	//UVerticalBox* audioMenu;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Audio")
	//USlider* masterVolumeSlider;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Audio")
	//USlider* musicVolumeSlider;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Audio")
	//USlider* sfxVolumeSlider;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Weapon")
	//UCanvasPanel* weaponSelectionPanel;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Primary Weapon")
	//UButton* primaryWeapon1Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Primary Weapon")
	//UButton* primaryWeapon2Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Primary Weapon")
	//UButton* primaryWeapon3Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Primary Weapon")
	//UButton* primaryWeaponBackButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Primary Weapon")
	//UEditableTextBox* primaryWeaponDescription;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Primary Weapon")
	//UImage* primaryWeaponImage;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Car")
	//UCanvasPanel* carCustomizationPanel;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Car")
	//UButton* car1Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Car")
	//UButton* car2Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Car")
	//UButton* car3Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Car")
	//UButton* car4Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Car")
	//UButton* carColor1Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Car")
	//UButton* carColor2Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Car")
	//UButton* carColor3Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Car")
	//UButton* carColor4Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Car")
	//UButton* tyreStyle1Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Car")
	//UButton* tyreStyle2Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Car")
	//UButton* tyreStyle3Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Car")
	//UButton* tyreStyle4Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Car")
	//UButton* carBackButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Car")
	//UImage* carImage;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Display")
	//UButton* displayBackButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Video")
	//UVerticalBox* videoMenu;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Video")
	//UCheckBox* fullScreenCheckBox;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Video")
	//USlider* brightnessSlider;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Video")
	//USlider* textureQualitySlider;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Video")
	//UButton* videoButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Difficulty")
	//UButton* easyButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Difficulty")
	//UButton* normalButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Difficulty")
	//UButton* hardButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Map")
	//UCanvasPanel* mapSelectionPanel;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Map")
	//UButton* map1Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Map")
	//UButton* map2Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Map")
	//UButton* map3Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Map")
	//UButton* map4Button;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Map")
	//UTextBlock* map1Text;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Map")
	//UTextBlock* map2Text;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Map")
	//UTextBlock* map3Text;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Map")
	//UTextBlock* map4Text;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Map")
	//UButton* mapBackButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Map")
	//UImage* mapImage;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Map")
	//UImage* mapTitleImage;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Map")
	//UEditableTextBox* mapDescription;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Singleplayer")
	//UButton* singleplayerButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Singleplayer")
	//UButton* singleplayerBackButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Singleplayer")
	//UVerticalBox* singleplayerMenu;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Multiplayer")
	//UButton* multiplayerBackButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Multiplayer")
	//UButton* multiplayerButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Multiplayer")
	//UVerticalBox* multiplayerMenu;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Quit")
	//UButton* noQuitButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Quit")
	//UButton* yesQuitButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Quit")
	//UButton* quitButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Quit")
	//UVerticalBox* quitMenu;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Quit")
	//UBorder* quitBackground;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Quit")
	//UHorizontalBox* quitChoices;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Options")
	//UButton* optionsBackButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Options")
	//UButton* optionsButton;
	//
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Options")
	//UVerticalBox* optionsMenu;
	//
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Booleans")
	//bool hasSelectedCar;
	//
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Booleans")
	//bool hasSelectedColor;
	//
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Booleans")
	//bool multiplayerMode;
};
