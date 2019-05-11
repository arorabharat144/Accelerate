// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "AccelerateUtility.h"
#include "MainMenuManager.h"
#include "GameManager.h"

//Sets default values
AMenuController::AMenuController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMenuController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMenuController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMenuController::HideMainMenu()
{
	//The order of the appearance of these menus might change, leading to the change in code here
	//if (mMainMenu != nullptr)
	//{
		//mMainMenu->menu->SetVisibility(ESlateVisibility::Collapsed);
		//mMainMenu->mapSelectionPanel->SetVisibility(ESlateVisibility::Collapsed);
		//
		//mMainMenu->carCustomizationPanel->SetVisibility(ESlateVisibility::Visible);
		//
		//mMainMenu->car1Button->SetUserFocus(this);
	//}
}

EPrimaryOffensiveWeaponTypes AMenuController::GetSelectedPrimaryWeapon() const
{
	return mSelectedPrimaryWeapon;
}

int32 AMenuController::GetID() const
{
	return mID;
}

void AMenuController::ChooseLaserBlaster()
{
	mSelectedPrimaryWeapon = EPrimaryOffensiveWeaponTypes::LaserBlaster;

	mGameManager->SetSelectedPrimaryWeapon(mID, mSelectedPrimaryWeapon);
}
void AMenuController::ChooseFlamethrower()
{
	mSelectedPrimaryWeapon = EPrimaryOffensiveWeaponTypes::Flamethrower;

	mGameManager->SetSelectedPrimaryWeapon(mID, mSelectedPrimaryWeapon);
}
void AMenuController::ChooseRailgun()
{
	mSelectedPrimaryWeapon = EPrimaryOffensiveWeaponTypes::Railgun;

	mGameManager->SetSelectedPrimaryWeapon(mID, mSelectedPrimaryWeapon);
}

void AMenuController::Initialize()
{
	//mMainMenu->primaryWeapon1Button->OnClicked.AddDynamic(this, &AMenuController::ChooseLaserBlaster);
	//mMainMenu->primaryWeapon2Button->OnClicked.AddDynamic(this, &AMenuController::ChooseFlamethrower);
	//mMainMenu->primaryWeapon3Button->OnClicked.AddDynamic(this, &AMenuController::ChooseRailgun);

	mGameManager = Cast<UGameManager>(GetGameInstance());

	mMainMenuManager = Cast<AMainMenuManager>(GetWorld()->GetAuthGameMode());

	SetID();

	InputComponent->BindAction("JoinGame", IE_Pressed, this, &AMenuController::OnPressedJoinGameKey);
	InputComponent->BindAction("Back", IE_Pressed, this, &AMenuController::OnPressedBackKey);

	InputComponent->BindAction("Start", IE_Pressed, this, &AMenuController::OnPressedstart);

	InputComponent->BindAction("SelectLeft", IE_Released, this, &AMenuController::OnPressedLeftKey);
	InputComponent->BindAction("SelectRight", IE_Released, this, &AMenuController::OnPressedRightKey);
}

void AMenuController::SetID()
{
	mID = UGameplayStatics::GetPlayerControllerID(this);
}

void AMenuController::OnPressedJoinGameKey()
{
	if (mGameManager->GetPlayerController(0) == this)
	{
		if (mMainMenuManager->GetMainMenu()->P1Active->GetVisibility() != ESlateVisibility::Visible)
		{
			mMainMenuManager->GetMainMenu()->P1InActive->SetVisibility(ESlateVisibility::Hidden);
			mMainMenuManager->GetMainMenu()->P1Active->SetVisibility(ESlateVisibility::Visible);
			mMainMenuManager->GetMainMenu()->p1MLeftArrow->SetUserFocus(this);
		}
	}
	else if (mGameManager->GetPlayerController(1) == this)
	{
		if (mMainMenuManager->GetMainMenu()->P2Active->GetVisibility() != ESlateVisibility::Visible)
		{
			mMainMenuManager->GetMainMenu()->P2InActive->SetVisibility(ESlateVisibility::Hidden);
			mMainMenuManager->GetMainMenu()->P2Active->SetVisibility(ESlateVisibility::Visible);
			mMainMenuManager->GetMainMenu()->p2MLeftArrow->SetUserFocus(this);
		}
	}
	else if (mGameManager->GetPlayerController(2) == this)
	{
		if (mMainMenuManager->GetMainMenu()->P3Active->GetVisibility() != ESlateVisibility::Visible)
		{
			mMainMenuManager->GetMainMenu()->P3InActive->SetVisibility(ESlateVisibility::Hidden);
			mMainMenuManager->GetMainMenu()->P3Active->SetVisibility(ESlateVisibility::Visible);
			mMainMenuManager->GetMainMenu()->p3MLeftArrow->SetUserFocus(this);
		}
	}
	else if (mGameManager->GetPlayerController(3) == this)
	{
		if (mMainMenuManager->GetMainMenu()->P4Active->GetVisibility() != ESlateVisibility::Visible)
		{
			mMainMenuManager->GetMainMenu()->P4InActive->SetVisibility(ESlateVisibility::Hidden);
			mMainMenuManager->GetMainMenu()->P4Active->SetVisibility(ESlateVisibility::Visible);
			mMainMenuManager->GetMainMenu()->p4MLeftArrow->SetUserFocus(this);
		}
	}
}

void AMenuController::OnPressedstart()
{
	if (mGameManager->GetPlayerController(0) == this)
	{
		if (mMainMenuManager->GetMainMenu()->carCustomizationMenu->GetVisibility() != ESlateVisibility::Visible)
		{
			uint32 numberOfPlayers{ 0 };
			for (uint32 i{ 0 }; i < static_cast<uint32_t>(mGameManager->GetMaximumPlayerCount()); ++i)
			{
				if (true == mMainMenuManager->GetPlayerReadyStatus(i))
				{
					numberOfPlayers++;
				}
			}

			mGameManager->SetNumberOfPlayers(numberOfPlayers);
			
			if (mMainMenuManager->GetSelectedModeEnum() == EModes::Race)
			{
				mGameManager->GetSelectedMode()->map = mMainMenuManager->GetMainMenu()->currentRaceTrackText->GetText().ToString();
			}
			else if (mMainMenuManager->GetSelectedModeEnum() == EModes::Battle)
			{
				mGameManager->GetSelectedMode()->map = mMainMenuManager->GetMainMenu()->currentBattleTrackText->GetText().ToString();
			}

			FString mapName{ AccelerateUtility::RemoveWhiteSpaces(mGameManager->GetSelectedMode()->map) };

			for (uint32 i{ 0 }; i < static_cast<uint32_t>(mGameManager->GetMaximumPlayerCount()); ++i)
			{
				if (false == mMainMenuManager->GetPlayerReadyStatus(i))
				{
					UGameplayStatics::RemovePlayer(mGameManager->GetPlayerController(i), true);
				}
			}

			EMaps currentMap{ AccelerateUtility::GetEnumFromString<EMaps, uint8>({ "EMaps" }, mapName) };
			mGameManager->LoadLevel(currentMap);
		}
		else if (mMainMenuManager->GetMainMenu()->raceMapSelectionPanel->GetVisibility() != ESlateVisibility::Visible)
		{
			if (mMainMenuManager->GetMainMenu()->p1Ready->IsChecked())
			{
				mMainMenuManager->SetPlayerReadyStatus(0, mMainMenuManager->GetMainMenu()->p1Ready->IsChecked());
				mMainMenuManager->SetPlayerReadyStatus(1, mMainMenuManager->GetMainMenu()->p2Ready->IsChecked());
				mMainMenuManager->SetPlayerReadyStatus(2, mMainMenuManager->GetMainMenu()->p3Ready->IsChecked());
				mMainMenuManager->SetPlayerReadyStatus(3, mMainMenuManager->GetMainMenu()->p4Ready->IsChecked());

				mMainMenuManager->GetMainMenu()->carCustomizationMenu->SetVisibility(ESlateVisibility::Hidden);

				if (mMainMenuManager->GetSelectedModeEnum() == EModes::Race)
				{
					mMainMenuManager->GetMainMenu()->raceMapSelectionPanel->SetVisibility(ESlateVisibility::Visible);

					//Setting values for player1
					TSharedPtr<RaceModeType> raceMode{ StaticCastSharedPtr<RaceModeType>(mGameManager->GetSelectedMode()) };
					raceMode->raceCarValues[0].model = mMainMenuManager->GetMainMenu()->p1ModelText->GetText().ToString();
					raceMode->raceCarValues[0].color = mMainMenuManager->GetMainMenu()->p1ColorText->GetText().ToString();

					//Checking if other players are enabled; if so, set their values
					if (true == mMainMenuManager->GetPlayerReadyStatus(1))
					{
						raceMode->raceCarValues[1].model = mMainMenuManager->GetMainMenu()->p2ModelText->GetText().ToString();
						raceMode->raceCarValues[1].color = mMainMenuManager->GetMainMenu()->p2ColorText->GetText().ToString();
					}
					if (true == mMainMenuManager->GetPlayerReadyStatus(2))
					{
						raceMode->raceCarValues[2].model = mMainMenuManager->GetMainMenu()->p3ModelText->GetText().ToString();
						raceMode->raceCarValues[2].color = mMainMenuManager->GetMainMenu()->p3ColorText->GetText().ToString();
					}
					if (true == mMainMenuManager->GetPlayerReadyStatus(3))
					{
						raceMode->raceCarValues[3].model = mMainMenuManager->GetMainMenu()->p4ModelText->GetText().ToString();
						raceMode->raceCarValues[3].color = mMainMenuManager->GetMainMenu()->p4ColorText->GetText().ToString();
					}
				}
				else if (mMainMenuManager->GetSelectedModeEnum() == EModes::Battle)
				{
					mMainMenuManager->GetMainMenu()->battleMapSelectionPanel->SetVisibility(ESlateVisibility::Visible);

					//Setting values for player1
					TSharedPtr<BattleModeType> battleMode{ StaticCastSharedPtr<BattleModeType>(mGameManager->GetSelectedMode()) };
					battleMode->battleCarValues[0].model = mMainMenuManager->GetMainMenu()->p1ModelText->GetText().ToString();
					battleMode->battleCarValues[0].color = mMainMenuManager->GetMainMenu()->p1ColorText->GetText().ToString();
					battleMode->battleCarValues[0].baseOffensive = mMainMenuManager->GetMainMenu()->p1BOText->GetText().ToString();
					battleMode->battleCarValues[0].baseDefensive = mMainMenuManager->GetMainMenu()->p1BDText->GetText().ToString();

					battleMode->battleCarValues[0].model = AccelerateUtility::RemoveWhiteSpaces(battleMode->battleCarValues[0].model);
					battleMode->battleCarValues[0].color = AccelerateUtility::RemoveWhiteSpaces(battleMode->battleCarValues[0].color);
					battleMode->battleCarValues[0].baseOffensive = AccelerateUtility::RemoveWhiteSpaces(battleMode->battleCarValues[0].baseOffensive);
					battleMode->battleCarValues[0].baseDefensive = AccelerateUtility::RemoveWhiteSpaces(battleMode->battleCarValues[0].baseDefensive);

					//Checking if other players are enabled; if so, set their values
					if (true == mMainMenuManager->GetPlayerReadyStatus(1))
					{
						battleMode->battleCarValues[1].model = mMainMenuManager->GetMainMenu()->p2ModelText->GetText().ToString();
						battleMode->battleCarValues[1].color = mMainMenuManager->GetMainMenu()->p2ColorText->GetText().ToString();
						battleMode->battleCarValues[1].baseOffensive = mMainMenuManager->GetMainMenu()->p2BOText->GetText().ToString();
						battleMode->battleCarValues[1].baseDefensive = mMainMenuManager->GetMainMenu()->p2BDText->GetText().ToString();

						battleMode->battleCarValues[1].model = AccelerateUtility::RemoveWhiteSpaces(battleMode->battleCarValues[1].model);
						battleMode->battleCarValues[1].color = AccelerateUtility::RemoveWhiteSpaces(battleMode->battleCarValues[1].color);
						battleMode->battleCarValues[1].baseOffensive = AccelerateUtility::RemoveWhiteSpaces(battleMode->battleCarValues[1].baseOffensive);
						battleMode->battleCarValues[1].baseDefensive = AccelerateUtility::RemoveWhiteSpaces(battleMode->battleCarValues[1].baseDefensive);
					}
					if (true == mMainMenuManager->GetPlayerReadyStatus(2))
					{
						battleMode->battleCarValues[2].model = mMainMenuManager->GetMainMenu()->p3ModelText->GetText().ToString();
						battleMode->battleCarValues[2].color = mMainMenuManager->GetMainMenu()->p3ColorText->GetText().ToString();
						battleMode->battleCarValues[2].baseOffensive = mMainMenuManager->GetMainMenu()->p3BOText->GetText().ToString();
						battleMode->battleCarValues[2].baseDefensive = mMainMenuManager->GetMainMenu()->p3BDText->GetText().ToString();

						battleMode->battleCarValues[2].model = AccelerateUtility::RemoveWhiteSpaces(battleMode->battleCarValues[2].model);
						battleMode->battleCarValues[2].color = AccelerateUtility::RemoveWhiteSpaces(battleMode->battleCarValues[2].color);
						battleMode->battleCarValues[2].baseOffensive = AccelerateUtility::RemoveWhiteSpaces(battleMode->battleCarValues[2].baseOffensive);
						battleMode->battleCarValues[2].baseDefensive = AccelerateUtility::RemoveWhiteSpaces(battleMode->battleCarValues[2].baseDefensive);
					}
					if (true == mMainMenuManager->GetPlayerReadyStatus(3))
					{
						battleMode->battleCarValues[3].model = mMainMenuManager->GetMainMenu()->p4ModelText->GetText().ToString();
						battleMode->battleCarValues[3].color = mMainMenuManager->GetMainMenu()->p4ColorText->GetText().ToString();
						battleMode->battleCarValues[3].baseOffensive = mMainMenuManager->GetMainMenu()->p4BOText->GetText().ToString();
						battleMode->battleCarValues[3].baseDefensive = mMainMenuManager->GetMainMenu()->p4BDText->GetText().ToString();

						battleMode->battleCarValues[3].model = AccelerateUtility::RemoveWhiteSpaces(battleMode->battleCarValues[3].model);
						battleMode->battleCarValues[3].color = AccelerateUtility::RemoveWhiteSpaces(battleMode->battleCarValues[3].color);
						battleMode->battleCarValues[3].baseOffensive = AccelerateUtility::RemoveWhiteSpaces(battleMode->battleCarValues[3].baseOffensive);
						battleMode->battleCarValues[3].baseDefensive = AccelerateUtility::RemoveWhiteSpaces(battleMode->battleCarValues[3].baseDefensive);
					}
				}
			}
		}
	}
}

void AMenuController::OnPressedLeftKey()
{
	if (mGameManager->GetPlayerController(0) == this)
	{
		if (mMainMenuManager->GetMainMenu()->carCustomizationMenu->GetVisibility() == ESlateVisibility::Visible)
		{
			if (mMainMenuManager->GetMainMenu()->p1MLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p1MRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(0, false, ECarCustomizations::Model);
			}
			else if (mMainMenuManager->GetMainMenu()->p1CLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p1CRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(0, false, ECarCustomizations::Color);
			}
			else if (mMainMenuManager->GetMainMenu()->p1BOLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p1BORightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(0, false, ECarCustomizations::BaseOffense);
			}
			else if (mMainMenuManager->GetMainMenu()->p1BDLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p1BDRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(0, false, ECarCustomizations::BaseDefense);
			}
		}
		else if (mMainMenuManager->GetMainMenu()->raceMapSelectionPanel->GetVisibility() == ESlateVisibility::Visible)
		{
			mMainMenuManager->GetMainMenu()->PreviousMap();
		}
	}
	else if (mGameManager->GetPlayerController(1) == this)
	{
		if (mMainMenuManager->GetMainMenu()->carCustomizationMenu->GetVisibility() == ESlateVisibility::Visible)
		{
			if (mMainMenuManager->GetMainMenu()->p2MLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p2MRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(1, false, ECarCustomizations::Model);
			}
			else if (mMainMenuManager->GetMainMenu()->p2CLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p2CRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(1, false, ECarCustomizations::Color);
			}
			else if (mMainMenuManager->GetMainMenu()->p2BOLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p2BORightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(1, false, ECarCustomizations::BaseOffense);
			}
			else if (mMainMenuManager->GetMainMenu()->p2BDLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p2BDRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(1, false, ECarCustomizations::BaseDefense);
			}
		}
	}
	else if (mGameManager->GetPlayerController(2) == this)
	{
		if (mMainMenuManager->GetMainMenu()->carCustomizationMenu->GetVisibility() == ESlateVisibility::Visible)
		{
			if (mMainMenuManager->GetMainMenu()->p3MLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p3MRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(2, false, ECarCustomizations::Model);
			}
			else if (mMainMenuManager->GetMainMenu()->p3CLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p3CRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(2, false, ECarCustomizations::Color);
			}
			else if (mMainMenuManager->GetMainMenu()->p3BOLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p3BORightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(2, false, ECarCustomizations::BaseOffense);
			}
			else if (mMainMenuManager->GetMainMenu()->p3BDLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p3BDRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(2, false, ECarCustomizations::BaseDefense);
			}
		}
	}
	else if (mGameManager->GetPlayerController(3) == this)
	{
		if (mMainMenuManager->GetMainMenu()->carCustomizationMenu->GetVisibility() == ESlateVisibility::Visible)
		{
			if (mMainMenuManager->GetMainMenu()->p4MLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p4MRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(3, false, ECarCustomizations::Model);
			}
			else if (mMainMenuManager->GetMainMenu()->p4CLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p4CRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(3, false, ECarCustomizations::Color);
			}
			else if (mMainMenuManager->GetMainMenu()->p4BOLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p4BORightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(3, false, ECarCustomizations::BaseOffense);
			}
			else if (mMainMenuManager->GetMainMenu()->p4BDLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p4BDRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(3, false, ECarCustomizations::BaseDefense);
			}
		}
	}
}

void AMenuController::OnPressedRightKey()
{
	if (mGameManager->GetPlayerController(0) == this)
	{
		if (mMainMenuManager->GetMainMenu()->carCustomizationMenu->GetVisibility() == ESlateVisibility::Visible)
		{
			if (mMainMenuManager->GetMainMenu()->p1MLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p1MRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(0, true, ECarCustomizations::Model);
			}
			else if (mMainMenuManager->GetMainMenu()->p1CLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p1CRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(0, true, ECarCustomizations::Color);
			}
			else if (mMainMenuManager->GetMainMenu()->p1BOLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p1BORightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(0, true, ECarCustomizations::BaseOffense);
			}
			else if (mMainMenuManager->GetMainMenu()->p1BDLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p1BDRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(0, true, ECarCustomizations::BaseDefense);
			}
		}
		else if (mMainMenuManager->GetMainMenu()->raceMapSelectionPanel->GetVisibility() == ESlateVisibility::Visible)
		{
			mMainMenuManager->GetMainMenu()->NextMap();
		}
	}
	else if (mGameManager->GetPlayerController(1) == this)
	{
		if (mMainMenuManager->GetMainMenu()->carCustomizationMenu->GetVisibility() == ESlateVisibility::Visible)
		{
			if (mMainMenuManager->GetMainMenu()->p2MLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p2MRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(1, true, ECarCustomizations::Model);
			}
			else if (mMainMenuManager->GetMainMenu()->p2CLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p2CRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(1, true, ECarCustomizations::Color);
			}
			else if (mMainMenuManager->GetMainMenu()->p2BOLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p2BORightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(1, true, ECarCustomizations::BaseOffense);
			}
			else if (mMainMenuManager->GetMainMenu()->p2BDLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p2BDRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(1, true, ECarCustomizations::BaseDefense);
			}
		}
	}
	else if (mGameManager->GetPlayerController(2) == this)
	{
		if (mMainMenuManager->GetMainMenu()->carCustomizationMenu->GetVisibility() == ESlateVisibility::Visible)
		{
			if (mMainMenuManager->GetMainMenu()->p3MLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p3MRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(2, true, ECarCustomizations::Model);
			}
			else if (mMainMenuManager->GetMainMenu()->p3CLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p3CRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(2, true, ECarCustomizations::Color);
			}
			else if (mMainMenuManager->GetMainMenu()->p3BOLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p3BORightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(2, true, ECarCustomizations::BaseOffense);
			}
			else if (mMainMenuManager->GetMainMenu()->p3BDLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p3BDRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(2, true, ECarCustomizations::BaseDefense);
			}
		}
	}
	else if (mGameManager->GetPlayerController(3) == this)
	{
		if (mMainMenuManager->GetMainMenu()->carCustomizationMenu->GetVisibility() == ESlateVisibility::Visible)
		{
			if (mMainMenuManager->GetMainMenu()->p4MLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p4MRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(3, true, ECarCustomizations::Model);
			}
			else if (mMainMenuManager->GetMainMenu()->p4CLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p4CRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(3, true, ECarCustomizations::Color);
			}
			else if (mMainMenuManager->GetMainMenu()->p4BOLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p4BORightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(3, true, ECarCustomizations::BaseOffense);
			}
			else if (mMainMenuManager->GetMainMenu()->p4BDLeftArrow->HasUserFocus(this) ||
				mMainMenuManager->GetMainMenu()->p4BDRightArrow->HasUserFocus(this))
			{
				mMainMenuManager->GetMainMenu()->IncreaseOrDecreaseValue(3, true, ECarCustomizations::BaseDefense);
			}
		}
	}
}

void AMenuController::OnPressedBackKey()
{
	if (mGameManager->GetPlayerController(0) != this)
	{
		return;
	}

	if (mMainMenuManager->GetMainMenu()->menu->GetVisibility() == ESlateVisibility::Visible)
	{
		mMainMenuManager->GetMainMenu()->menu->SetVisibility(ESlateVisibility::Collapsed);
		mMainMenuManager->GetMainMenu()->quitMenu->SetVisibility(ESlateVisibility::Visible);
		mMainMenuManager->GetMainMenu()->yesQuitButton->SetUserFocus(this);
	}
	else if (mMainMenuManager->GetMainMenu()->carCustomizationMenu->GetVisibility() == ESlateVisibility::Visible)
	{
		mMainMenuManager->GetMainMenu()->p1Ready->SetCheckedState(ECheckBoxState::Unchecked);
		mMainMenuManager->GetMainMenu()->p2Ready->SetCheckedState(ECheckBoxState::Unchecked);
		mMainMenuManager->GetMainMenu()->p3Ready->SetCheckedState(ECheckBoxState::Unchecked);
		mMainMenuManager->GetMainMenu()->p4Ready->SetCheckedState(ECheckBoxState::Unchecked);

		mMainMenuManager->GetMainMenu()->raceButton->SetVisibility(ESlateVisibility::Hidden);
		mMainMenuManager->GetMainMenu()->unlitRace->SetVisibility(ESlateVisibility::Visible);

		for (uint32 i{ 1 }; i < static_cast<uint32>(mGameManager->GetMaximumPlayerCount()); ++i) //4 is the number of maximum players the game can support
		{
			mMainMenuManager->GetMainMenu()->raceBackButton->SetUserFocus(mGameManager->GetPlayerController(i));
		}

		mMainMenuManager->GetMainMenu()->carCustomizationMenu->SetVisibility(ESlateVisibility::Collapsed);
		mMainMenuManager->GetMainMenu()->menu->SetVisibility(ESlateVisibility::Visible);
		mMainMenuManager->GetMainMenu()->raceModeButton->SetUserFocus(this);
	}
	else if (mMainMenuManager->GetMainMenu()->optionsMenu->GetVisibility() == ESlateVisibility::Visible)
	{
		mMainMenuManager->GetMainMenu()->optionsMenu->SetVisibility(ESlateVisibility::Collapsed);
		mMainMenuManager->GetMainMenu()->menu->SetVisibility(ESlateVisibility::Visible);
		mMainMenuManager->GetMainMenu()->raceModeButton->SetUserFocus(this);
	}
	else if (mMainMenuManager->GetMainMenu()->videoMenu->GetVisibility() == ESlateVisibility::Visible)
	{
		mMainMenuManager->GetMainMenu()->videoMenu->SetVisibility(ESlateVisibility::Collapsed);
		mMainMenuManager->GetMainMenu()->optionsMenu->SetVisibility(ESlateVisibility::Visible);
		mMainMenuManager->GetMainMenu()->videoButton->SetUserFocus(this);
	}
	else if (mMainMenuManager->GetMainMenu()->audioMenu->GetVisibility() == ESlateVisibility::Visible)
	{
		mMainMenuManager->GetMainMenu()->audioMenu->SetVisibility(ESlateVisibility::Collapsed);
		mMainMenuManager->GetMainMenu()->optionsMenu->SetVisibility(ESlateVisibility::Visible);
		mMainMenuManager->GetMainMenu()->videoButton->SetUserFocus(this);
	}
	else if (mMainMenuManager->GetMainMenu()->raceMapSelectionPanel->GetVisibility() == ESlateVisibility::Visible)
	{
		mMainMenuManager->GetMainMenu()->raceMapSelectionPanel->SetVisibility(ESlateVisibility::Collapsed);
		mMainMenuManager->GetMainMenu()->carCustomizationMenu->SetVisibility(ESlateVisibility::Visible);
	}
	else if (mMainMenuManager->GetMainMenu()->quitMenu->GetVisibility() == ESlateVisibility::Visible)
	{
		mMainMenuManager->GetMainMenu()->quitMenu->SetVisibility(ESlateVisibility::Collapsed);
		mMainMenuManager->GetMainMenu()->menu->SetVisibility(ESlateVisibility::Visible);
		mMainMenuManager->GetMainMenu()->raceModeButton->SetUserFocus(this);
	}
}