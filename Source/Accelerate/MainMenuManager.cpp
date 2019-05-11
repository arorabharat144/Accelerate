// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuManager.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "GameManager.h"

#include "MenuController.h"
#include "CarController.h"

#include "MainMenu.h"
#include "AccelerateUtility.h"
//#include "LoadingModule.h"

AMainMenuManager::AMainMenuManager()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AMainMenuManager::BeginPlay()
{
	Super::BeginPlay();

	mGameManager = Cast<UGameManager>(GetGameInstance());

	const UWorld* world{ GetWorld() };

	world->GetGameViewport()->SetDisableSplitscreenOverride(true);

	mGameManager->mPlayers.Empty();
	//mGameManager->mPlayerControllers.Empty();

	if (!mGameManager->hasCreatedPlayers)
	{
		mGameManager->mPlayerControllers.Add(Cast<AMenuController>(world->GetFirstPlayerController()));

		Cast<AMenuController>(mGameManager->mPlayerControllers.Last())->Initialize();
		for (uint32 i{ 1 }; i < static_cast<uint32>(mGameManager->GetMaximumPlayerCount()); ++i) //4 is the number of maximum players the game can support
		{
			mGameManager->mPlayerControllers.Add(Cast<AMenuController>(UGameplayStatics::CreatePlayer(world))); //Calling BeginPlay before creating the new menu
			Cast<AMenuController>(mGameManager->mPlayerControllers[i])->Initialize();
			//mMainMenu->raceModeButton->SetUserFocus(mGameManager->mPlayerControllers[i]);
		}
	}
	else
	{
		mGameManager->mPlayerControllers[0] = Cast<AMenuController>(UGameplayStatics::GetPlayerController(world, 0));
		Cast<AMenuController>(mGameManager->mPlayerControllers[0])->Initialize();
		for (uint32 i{ 1 }; i < static_cast<uint32>(mGameManager->GetMaximumPlayerCount()); ++i)
		{
			mGameManager->mPlayerControllers[i] = Cast<AMenuController>(UGameplayStatics::CreatePlayer(world));
			Cast<AMenuController>(mGameManager->mPlayerControllers[i])->Initialize();
		}
	}

	CreateMenu();

	Initialize();

	mGameManager->hasCreatedPlayers = true;

	mPlayerReadyStatuses.Init(false, mGameManager->mPlayerControllers.Num());

	InitializeButtonStyles();
	InitializeCarCustomizationButtonStyles();
	InitializeCheckBoxesStyles();

	//Cast<AMenuController>(mGameManager->mPlayerControllers[0])->GetMainMenu()->map1Button->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressedMap1Button);
	//Cast<AMenuController>(mGameManager->mPlayerControllers[0])->GetMainMenu()->map2Button->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressedMap2Button);
	//Cast<AMenuController>(mGameManager->mPlayerControllers[0])->GetMainMenu()->map3Button->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressedMap3Button);
	//Cast<AMenuController>(mGameManager->mPlayerControllers[0])->GetMainMenu()->map4Button->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressedMap4Button);
	//
	//Cast<AMenuController>(mGameManager->mPlayerControllers[0])->GetMainMenu()->primaryWeapon1Button->OnClicked.AddDynamic(this, &AMainMenuManager::CheckAndUpdateLevel);
	//Cast<AMenuController>(mGameManager->mPlayerControllers[0])->GetMainMenu()->primaryWeapon2Button->OnClicked.AddDynamic(this, &AMainMenuManager::CheckAndUpdateLevel);
	//Cast<AMenuController>(mGameManager->mPlayerControllers[0])->GetMainMenu()->primaryWeapon3Button->OnClicked.AddDynamic(this, &AMainMenuManager::CheckAndUpdateLevel);
}

void AMainMenuManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mMainMenu->carCustomizationMenu->GetVisibility() != ESlateVisibility::Visible)
	{
		UpdateButtonStyles();
	}
	else
	{
		UpdateCarCustomizationButtonStyles();
		UpdateCheckBoxesStyles();
	}
}

UMainMenu* AMainMenuManager::GetMainMenu() const
{
	return mMainMenu;
}

bool AMainMenuManager::GetPlayerReadyStatus(uint32 index)
{
	return mPlayerReadyStatuses[index];
}

void AMainMenuManager::SetPlayerReadyStatus(uint32 index, bool status)
{
	mPlayerReadyStatuses[index] = status;
}

EModes AMainMenuManager::GetSelectedModeEnum() const
{
	return mSelectedMode;
}

MyButtonStyle AMainMenuManager::GetButtonStyle(uint32 index) const
{
	return mButtonStyles[index];
}

MyCarCustomizationButtonStyle AMainMenuManager::GetCarCustomizationMenuButtonStyle(uint32 index) const
{
	return mCarCustomizationButtonStyles[index];
}

void AMainMenuManager::CreateMenu()
{
	if (mainMenuRef != nullptr)
	{
		mMainMenu = Cast<UMainMenu>(CreateWidget(mGameManager->mPlayerControllers[0], mainMenuRef));

		if (mMainMenu != nullptr)
		{
			mMainMenu->AddToViewport();
			mMainMenu->raceModeButton->SetUserFocus(mGameManager->mPlayerControllers[0]);


			//BindDelegates();
			//SetID();
		}
	}
}

void AMainMenuManager::Initialize()
{
	mMainMenu->raceModeButton->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressedraceModeButton);
	mMainMenu->battleModeButton->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressedbattleModeButton);
	mMainMenu->optionsButton->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressedoptionsButton);
	mMainMenu->quitButton->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressedquitButton);
	mMainMenu->raceBackButton->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressedraceBackButton);
	mMainMenu->raceButton->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressedraceButton);
	mMainMenu->videoButton->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressedvideoButton);
	mMainMenu->audioButton->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressedaudioButton);
	mMainMenu->optionsBackButton->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressedoptionsBackButton);
	mMainMenu->yesQuitButton->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressedyesQuitButton);
	mMainMenu->noQuitButton->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressednoQuitButton);
	mMainMenu->displayBackButton->OnClicked.AddDynamic(this, &AMainMenuManager::OnPresseddisplayBackButton);
	mMainMenu->audioBackButton->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressedaudioBackButton);
	mMainMenu->mapBackButton->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressedmapBackButton);
	mMainMenu->mapSpaceButton->OnClicked.AddDynamic(this, &AMainMenuManager::OnPressedmapSpaceButton);

	mMainMenu->fullScreenCheckBox->OnCheckStateChanged.AddDynamic(this, &AMainMenuManager::OnToggleFullscreen);
	mMainMenu->p1Ready->OnCheckStateChanged.AddDynamic(this, &AMainMenuManager::OnToggleP1Ready);
	mMainMenu->p2Ready->OnCheckStateChanged.AddDynamic(this, &AMainMenuManager::OnToggleP2Ready);
	mMainMenu->p3Ready->OnCheckStateChanged.AddDynamic(this, &AMainMenuManager::OnToggleP3Ready);
	mMainMenu->p4Ready->OnCheckStateChanged.AddDynamic(this, &AMainMenuManager::OnToggleP4Ready);

	//Cast<AMenuController>(mGameManager->mPlayerControllers[index])->GetMainMenu()->map1Button->OnClicked.AddDynamic(this, &AMainMenuManager::AddAdditionalPlayers);
	//Cast<AMenuController>(mGameManager->mPlayerControllers[index])->GetMainMenu()->map2Button->OnClicked.AddDynamic(this, &AMainMenuManager::AddAdditionalPlayers);
	//Cast<AMenuController>(mGameManager->mPlayerControllers[index])->GetMainMenu()->map3Button->OnClicked.AddDynamic(this, &AMainMenuManager::AddAdditionalPlayers);
	//Cast<AMenuController>(mGameManager->mPlayerControllers[index])->GetMainMenu()->map4Button->OnClicked.AddDynamic(this, &AMainMenuManager::AddAdditionalPlayers);
	//Cast<AMenuController>(mGameManager->mPlayerControllers[index])->GetMainMenu()->primaryWeapon1Button->OnClicked.AddDynamic(this, &AMainMenuManager::CheckAndUpdateLevel);
	//Cast<AMenuController>(mGameManager->mPlayerControllers[index])->GetMainMenu()->primaryWeapon2Button->OnClicked.AddDynamic(this, &AMainMenuManager::CheckAndUpdateLevel);
	//Cast<AMenuController>(mGameManager->mPlayerControllers[index])->GetMainMenu()->primaryWeapon3Button->OnClicked.AddDynamic(this, &AMainMenuManager::CheckAndUpdateLevel);
}

void AMainMenuManager::InitializeButtonStyles()
{
	for (uint32 i{ 0 }; i < static_cast<uint32>(mMainMenu->GetButtons().Num()); ++i)
	{
		FButtonStyle buttonStyle{ mMainMenu->GetButtons()[i]->WidgetStyle };
		MyButtonStyle myButtonStyle;

		myButtonStyle.normalStyle.SetNormal(buttonStyle.Normal);
		myButtonStyle.hoveredStyle.SetNormal(buttonStyle.Hovered);
		myButtonStyle.pressedStyle.SetNormal(buttonStyle.Pressed);

		mButtonStyles.Add(myButtonStyle);
	}
}

void AMainMenuManager::InitializeCarCustomizationButtonStyles()
{
	for (uint32 i{ 0 }; i < static_cast<uint32>(mMainMenu->GetCarCustomizationMenuButtons().Num()); ++i)
	{
		FButtonStyle carCustomizationLeftButtonStyle{ mMainMenu->GetCarCustomizationMenuButtons()[i].left->WidgetStyle };
		FButtonStyle carCustomizationRightButtonStyle{ mMainMenu->GetCarCustomizationMenuButtons()[i].right->WidgetStyle };

		MyCarCustomizationButtonStyle myCarCustomizationButtonStyle;

		myCarCustomizationButtonStyle.leftStyle.normalStyle.SetNormal(carCustomizationLeftButtonStyle.Normal);
		myCarCustomizationButtonStyle.leftStyle.hoveredStyle.SetNormal(carCustomizationLeftButtonStyle.Hovered);
		myCarCustomizationButtonStyle.leftStyle.pressedStyle.SetNormal(carCustomizationLeftButtonStyle.Pressed);

		myCarCustomizationButtonStyle.rightStyle.normalStyle.SetNormal(carCustomizationRightButtonStyle.Normal);
		myCarCustomizationButtonStyle.rightStyle.hoveredStyle.SetNormal(carCustomizationRightButtonStyle.Hovered);
		myCarCustomizationButtonStyle.rightStyle.pressedStyle.SetNormal(carCustomizationRightButtonStyle.Pressed);

		mCarCustomizationButtonStyles.Add(myCarCustomizationButtonStyle);
	}
}

void AMainMenuManager::InitializeCheckBoxesStyles()
{
	for (uint32 i{ 0 }; i < static_cast<uint32>(mMainMenu->GetCheckBoxes().Num()); ++i)
	{
		FCheckBoxStyle checkBoxStyle{ mMainMenu->GetCheckBoxes()[i]->WidgetStyle };
		MyCheckboxStyle myCheckBoxStyle;

		myCheckBoxStyle.uncheckedStyle.SetUncheckedImage(checkBoxStyle.UncheckedImage);
		myCheckBoxStyle.uncheckedHoveredStyle.SetUncheckedImage(checkBoxStyle.UncheckedHoveredImage);
		myCheckBoxStyle.uncheckedPressedStyle.SetUncheckedPressedImage(checkBoxStyle.UncheckedPressedImage);
		myCheckBoxStyle.checkedStyle.SetCheckedImage(checkBoxStyle.CheckedImage);
		myCheckBoxStyle.checkedHoveredStyle.SetCheckedImage(checkBoxStyle.CheckedHoveredImage);
		myCheckBoxStyle.checkedPressedStyle.SetCheckedPressedImage(checkBoxStyle.CheckedPressedImage);

		mCheckboxStyles.Add(myCheckBoxStyle);
	}
}

void AMainMenuManager::UpdateButtonStyles()
{
	for (uint32 i{ 0 }; i < static_cast<uint32>(mMainMenu->GetButtons().Num()); ++i)
	{
		UButton* button{ mMainMenu->GetButtons()[i] };
		MyButtonStyle myButtonStyle{ mButtonStyles[i] };

		if (button->HasAnyUserFocus())
		{
			if (button->IsPressed())
			{
				button->SetStyle(myButtonStyle.pressedStyle);
			}
			else
			{
				button->SetStyle(myButtonStyle.hoveredStyle);
			}
		}
		else
		{
			button->SetStyle(myButtonStyle.normalStyle);
		}
	}
}

void AMainMenuManager::UpdateCarCustomizationButtonStyles()
{
	for (uint32 i{ 0 }; i < static_cast<uint32>(mMainMenu->GetCarCustomizationMenuButtons().Num()); ++i)
	{
		UMainMenu::CarCustomizationButton carCustomizationButton{ mMainMenu->GetCarCustomizationMenuButtons()[i] };
		MyCarCustomizationButtonStyle myCarCustomizationButtonStyle{ mCarCustomizationButtonStyles[i] };

		if (carCustomizationButton.left->HasAnyUserFocus() || carCustomizationButton.right->HasAnyUserFocus())
		{
			carCustomizationButton.left->SetStyle(myCarCustomizationButtonStyle.leftStyle.hoveredStyle);
			carCustomizationButton.right->SetStyle(myCarCustomizationButtonStyle.rightStyle.hoveredStyle);
		}
		else
		{
			carCustomizationButton.left->SetStyle(myCarCustomizationButtonStyle.leftStyle.normalStyle);
			carCustomizationButton.right->SetStyle(myCarCustomizationButtonStyle.rightStyle.normalStyle);
		}
	}
}

void AMainMenuManager::UpdateCheckBoxesStyles()
{
	for (uint32 i{ 0 }; i < static_cast<uint32>(mMainMenu->GetCheckBoxes().Num()); ++i)
	{
		UCheckBox* checkBox{ mMainMenu->GetCheckBoxes()[i] };
		MyCheckboxStyle myCheckBoxStyle{ mCheckboxStyles[i] };

		if (checkBox->HasAnyUserFocus())
		{
			if (checkBox->IsChecked())
			{
				if (checkBox->IsPressed())
				{
					checkBox->WidgetStyle = myCheckBoxStyle.checkedPressedStyle;
				}
				else
				{
					checkBox->WidgetStyle = myCheckBoxStyle.checkedHoveredStyle;
				}
			}
			else
			{
				if (checkBox->IsPressed())
				{
					checkBox->WidgetStyle = myCheckBoxStyle.uncheckedPressedStyle;
				}
				else
				{
					checkBox->WidgetStyle = myCheckBoxStyle.uncheckedHoveredStyle;
				}
			}
		}
		else
		{
			if (checkBox->IsChecked())
			{
				checkBox->WidgetStyle = myCheckBoxStyle.checkedStyle;
			}
			else
			{
				checkBox->WidgetStyle = myCheckBoxStyle.uncheckedStyle;
			}
		}
	}
}

void AMainMenuManager::OnPressedraceModeButton()
{
	for (uint32 i{ 1 }; i < static_cast<uint32>(mGameManager->GetMaximumPlayerCount()); ++i) //4 is the number of maximum players the game can support
	{
		mMainMenu->raceModeButton->SetUserFocus(mGameManager->mPlayerControllers[i]);
	}

	mMainMenu->menu->SetVisibility(ESlateVisibility::Collapsed);
	mMainMenu->carCustomizationMenu->SetVisibility(ESlateVisibility::Visible);

	mMainMenu->p1BaseOffenseWeaponSelection->SetVisibility(ESlateVisibility::Collapsed);
	mMainMenu->p2BaseOffenseWeaponSelection->SetVisibility(ESlateVisibility::Collapsed);
	mMainMenu->p3BaseOffenseWeaponSelection->SetVisibility(ESlateVisibility::Collapsed);
	mMainMenu->p4BaseOffenseWeaponSelection->SetVisibility(ESlateVisibility::Collapsed);

	mMainMenu->p1BaseDefenseWeaponSelection->SetVisibility(ESlateVisibility::Collapsed);
	mMainMenu->p2BaseDefenseWeaponSelection->SetVisibility(ESlateVisibility::Collapsed);
	mMainMenu->p3BaseDefenseWeaponSelection->SetVisibility(ESlateVisibility::Collapsed);
	mMainMenu->p4BaseDefenseWeaponSelection->SetVisibility(ESlateVisibility::Collapsed);

	mMainMenu->P1InActive->SetVisibility(ESlateVisibility::Visible);
	mMainMenu->P2InActive->SetVisibility(ESlateVisibility::Visible);
	mMainMenu->P3InActive->SetVisibility(ESlateVisibility::Visible);
	mMainMenu->P4InActive->SetVisibility(ESlateVisibility::Visible);

	mMainMenu->P1Active->SetVisibility(ESlateVisibility::Hidden);
	mMainMenu->P2Active->SetVisibility(ESlateVisibility::Hidden);
	mMainMenu->P3Active->SetVisibility(ESlateVisibility::Hidden);
	mMainMenu->P4Active->SetVisibility(ESlateVisibility::Hidden);

	mSelectedMode = EModes::Race;
	mGameManager->mCurrentModeType = MakeShared<RaceModeType>();
	StaticCastSharedPtr<RaceModeType>(mGameManager->mCurrentModeType)->raceCarValues.Init({}, mGameManager->GetMaximumPlayerCount());
}

void AMainMenuManager::OnPressedbattleModeButton()
{
	mMainMenu->menu->SetVisibility(ESlateVisibility::Collapsed);
	mMainMenu->carCustomizationMenu->SetVisibility(ESlateVisibility::Visible);

	mMainMenu->p1BaseOffenseWeaponSelection->SetVisibility(ESlateVisibility::Visible);
	mMainMenu->p2BaseOffenseWeaponSelection->SetVisibility(ESlateVisibility::Visible);
	mMainMenu->p3BaseOffenseWeaponSelection->SetVisibility(ESlateVisibility::Visible);
	mMainMenu->p4BaseOffenseWeaponSelection->SetVisibility(ESlateVisibility::Visible);

	mMainMenu->p1BaseDefenseWeaponSelection->SetVisibility(ESlateVisibility::Visible);
	mMainMenu->p2BaseDefenseWeaponSelection->SetVisibility(ESlateVisibility::Visible);
	mMainMenu->p3BaseDefenseWeaponSelection->SetVisibility(ESlateVisibility::Visible);
	mMainMenu->p4BaseDefenseWeaponSelection->SetVisibility(ESlateVisibility::Visible);

	mMainMenu->P1InActive->SetVisibility(ESlateVisibility::Visible);
	mMainMenu->P2InActive->SetVisibility(ESlateVisibility::Visible);
	mMainMenu->P3InActive->SetVisibility(ESlateVisibility::Visible);
	mMainMenu->P4InActive->SetVisibility(ESlateVisibility::Visible);

	mMainMenu->P1Active->SetVisibility(ESlateVisibility::Hidden);
	mMainMenu->P2Active->SetVisibility(ESlateVisibility::Hidden);
	mMainMenu->P3Active->SetVisibility(ESlateVisibility::Hidden);
	mMainMenu->P4Active->SetVisibility(ESlateVisibility::Hidden);

	mSelectedMode = EModes::Battle;
	mGameManager->mCurrentModeType = MakeShared<BattleModeType>();
	StaticCastSharedPtr<BattleModeType>(mGameManager->mCurrentModeType)->battleCarValues.Init({}, mGameManager->GetMaximumPlayerCount());
}

void AMainMenuManager::OnPressedoptionsButton()
{
	mMainMenu->menu->SetVisibility(ESlateVisibility::Collapsed);
	mMainMenu->optionsMenu->SetVisibility(ESlateVisibility::Visible);

	mMainMenu->videoButton->SetUserFocus(mGameManager->mPlayerControllers[0]);
}

void AMainMenuManager::OnPressedquitButton()
{
	mMainMenu->menu->SetVisibility(ESlateVisibility::Collapsed);
	mMainMenu->quitMenu->SetVisibility(ESlateVisibility::Visible);

	mMainMenu->yesQuitButton->SetUserFocus(mGameManager->mPlayerControllers[0]);
}

void AMainMenuManager::OnPressedraceBackButton()
{
	//Dont know if should implement
}

void AMainMenuManager::OnPressedraceButton()
{
}

void AMainMenuManager::OnPressedvideoButton()
{
	mMainMenu->optionsMenu->SetVisibility(ESlateVisibility::Collapsed);
	mMainMenu->videoMenu->SetVisibility(ESlateVisibility::Visible);

	mMainMenu->fullScreenCheckBox->SetUserFocus(mGameManager->GetPlayerController(0));
}

void AMainMenuManager::OnToggleFullscreen(bool isChecked)
{
	//TODO: Check if it works
	mGameManager->ToggleFullscreen(isChecked);
}

void AMainMenuManager::OnToggleP1Ready(bool isChecked)
{
	if (isChecked)
	{
		mMainMenu->unlitRace->SetVisibility(ESlateVisibility::Hidden);
		mMainMenu->raceButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		mMainMenu->raceButton->SetVisibility(ESlateVisibility::Hidden);
		mMainMenu->unlitRace->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainMenuManager::OnToggleP2Ready(bool isChecked)
{

}

void AMainMenuManager::OnToggleP3Ready(bool isChecked)
{

}

void AMainMenuManager::OnToggleP4Ready(bool isChecked)
{

}

void AMainMenuManager::OnPressedaudioButton()
{
	mMainMenu->optionsMenu->SetVisibility(ESlateVisibility::Collapsed);
	mMainMenu->audioMenu->SetVisibility(ESlateVisibility::Visible);

	mMainMenu->masterVolumeSlider->SetUserFocus(mGameManager->GetPlayerController(0));
}

void AMainMenuManager::OnPressedoptionsBackButton()
{
	mMainMenu->optionsMenu->SetVisibility(ESlateVisibility::Collapsed);
	mMainMenu->menu->SetVisibility(ESlateVisibility::Visible);

	mMainMenu->raceModeButton->SetUserFocus(mGameManager->GetPlayerController(0));
}

void AMainMenuManager::OnPressedyesQuitButton()
{
	mGameManager->QuitGame();
}

void AMainMenuManager::OnPressednoQuitButton()
{
	mMainMenu->quitMenu->SetVisibility(ESlateVisibility::Collapsed);
	mMainMenu->menu->SetVisibility(ESlateVisibility::Visible);

	mMainMenu->raceModeButton->SetUserFocus(mGameManager->GetPlayerController(0));
}

void AMainMenuManager::OnPresseddisplayBackButton()
{
	mMainMenu->videoMenu->SetVisibility(ESlateVisibility::Collapsed);
	mMainMenu->optionsMenu->SetVisibility(ESlateVisibility::Visible);

	mMainMenu->videoButton->SetUserFocus(mGameManager->GetPlayerController(0));
}

void AMainMenuManager::OnPressedaudioBackButton()
{
	mMainMenu->audioMenu->SetVisibility(ESlateVisibility::Collapsed);
	mMainMenu->optionsMenu->SetVisibility(ESlateVisibility::Visible);

	mMainMenu->videoButton->SetUserFocus(mGameManager->GetPlayerController(0));
}

void AMainMenuManager::OnPressedmapBackButton()
{
	//Dont know if should implement
}

void AMainMenuManager::OnPressedmapSpaceButton()
{
}

void AMainMenuManager::AddAdditionalPlayers()
{
	const UWorld* world{ GetWorld() };
	if (mGameManager->GetNumberOfPlayers() > 1)
	{
		for (uint32 i{ 1 }; i < static_cast<uint32>(mGameManager->GetNumberOfPlayers()); ++i)
		{
			mGameManager->mPlayerControllers.Add(Cast<AMenuController>(UGameplayStatics::CreatePlayer(world))); //Calling BeginPlay before creating the new menu
			//Cast<AMenuController>(mGameManager->mPlayerControllers[i])->CreateMenu();
			//BindDelegates(i);
		}

		//for (uint32 i{ 0 }; i < static_cast<uint32>(mGameManager->GetNumberOfPlayers()); ++i)
		//{
		//	Cast<AMenuController>(mGameManager->mPlayerControllers[i])->HideMainMenu();
		//}
	}
}