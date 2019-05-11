// Fill out your copyright notice in the Description page of Project Settings.

#include "CarController.h"
#include "GameManager.h"
#include "UserWidget.h"
#include "GameFramework/GameModeBase.h"

#include "Classes/Kismet/GameplayStatics.h"

//Sets default values
ACarController::ACarController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACarController::BeginPlay()
{
	Super::BeginPlay();

	InitializePauseMenu();
}

// Called every frame
void ACarController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		UpdatePauseMenu(DeltaTime);
	}
}

void ACarController::CreateRaceHUD()
{
	if (raceHudRef != nullptr)
	{
		mHud = CreateWidget(this, raceHudRef);

		if (mHud != nullptr)
		{
			mHud->AddToPlayerScreen();
		}
	}
}

void ACarController::CreateBattleHUD()
{
	if (raceHudRef != nullptr)
	{
		mHud = CreateWidget(this, battleHudRef);

		if (mHud != nullptr)
		{
			mHud->AddToPlayerScreen();
		}
	}
}

void ACarController::CreatePauseMenu()
{
	if (pauseMenuRef != nullptr)
	{
		mPauseMenu = Cast<UPauseMenu>(CreateWidget(this, pauseMenuRef));
	}
}

void ACarController::InitializePauseMenu()
{
	InputComponent->BindAction("Pause", IE_Pressed, this, &ACarController::OnPressedPause);
	InputComponent->BindAction("Unpause", IE_Pressed, this, &ACarController::OnPressedUnpause).bExecuteWhenPaused = true;

	InputComponent->BindAction("ConfirmRestartYes", IE_Pressed, this, &ACarController::OnPressedYesRestart).bExecuteWhenPaused = true;
	InputComponent->BindAction("ConfirmRestartNo", IE_Pressed, this, &ACarController::OnPressedNoRestart).bExecuteWhenPaused = true;

	InputComponent->BindAction("ConfirmMainMenuYes", IE_Pressed, this, &ACarController::OnPressedYesMainMenu).bExecuteWhenPaused = true;
	InputComponent->BindAction("ConfirmMainMenuNo", IE_Pressed, this, &ACarController::OnPressedNoMainMenu).bExecuteWhenPaused = true;

	mPauseMenu->resumeButton->OnClicked.AddDynamic(this, &ACarController::OnPressedUnpause);
	mPauseMenu->restartButton->OnClicked.AddDynamic(this, &ACarController::OnPressedRestart);
	mPauseMenu->mainMenuButton->OnClicked.AddDynamic(this, &ACarController::OnPressedMainMenu);

	for (uint32 i{ 0 }; i < static_cast<uint32>(mPauseMenu->GetButtons().Num()); ++i)
	{
		FButtonStyle buttonStyle{ mPauseMenu->GetButtons()[i]->WidgetStyle };
		MyButtonStyle myButtonStyle;

		myButtonStyle.normalStyle.SetNormal(buttonStyle.Normal);
		myButtonStyle.hoveredStyle.SetNormal(buttonStyle.Hovered);
		myButtonStyle.pressedStyle.SetNormal(buttonStyle.Pressed);

		mButtonStyles.Add(myButtonStyle);
	}
}

void ACarController::UpdatePauseMenu(float deltaTime)
{
	for (uint32 i{ 0 }; i < static_cast<uint32>(mPauseMenu->GetButtons().Num()); ++i)
	{
		UButton* button{ mPauseMenu->GetButtons()[i] };
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

void ACarController::OnPressedPause()
{
	if (!UGameplayStatics::IsGamePaused(GetWorld()))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		mPauseController = this;

		mPauseMenu->AddToViewport();

		mPauseMenu->resumeButton->SetUserFocus(this);
	}
}

void ACarController::OnPressedUnpause()
{
	if (this == mPauseController)
	{
		if (UGameplayStatics::IsGamePaused(GetWorld()))
		{
			if (!hasOpenedRestartConfirmationScreen && !hasOpenedMainMenuConfirmationScreen)
			{
				UGameplayStatics::SetGamePaused(GetWorld(), false);

				mPauseMenu->RemoveFromViewport();

				mPauseController = nullptr;
			}
		}
	}
}

void ACarController::OnPressedRestart()
{
	if (this == mPauseController)
	{
		mPauseMenu->pauseContainer->SetVisibility(ESlateVisibility::Hidden);
		mPauseMenu->restartConfirmation->SetVisibility(ESlateVisibility::Visible);

		hasOpenedRestartConfirmationScreen = true;
	}
}

void ACarController::OnPressedYesRestart()
{
	if (this == mPauseController)
	{
		if (hasOpenedRestartConfirmationScreen)
		{
			UGameManager* gameManager{ Cast<UGameManager>(GetGameInstance()) };
			gameManager->LoadLevel(gameManager->GetCurrentMap());

			hasOpenedRestartConfirmationScreen = false;
		}
	}
}

void ACarController::OnPressedNoRestart()
{
	if (this == mPauseController)
	{
		if (hasOpenedRestartConfirmationScreen)
		{
			mPauseMenu->restartConfirmation->SetVisibility(ESlateVisibility::Hidden);
			mPauseMenu->pauseContainer->SetVisibility(ESlateVisibility::Visible);

			mPauseMenu->resumeButton->SetUserFocus(this);

			hasOpenedRestartConfirmationScreen = false;
		}
	}
}

void ACarController::OnPressedMainMenu()
{
	if (this == mPauseController)
	{
		mPauseMenu->pauseContainer->SetVisibility(ESlateVisibility::Hidden);
		mPauseMenu->mainMenuConfirmation->SetVisibility(ESlateVisibility::Visible);

		hasOpenedMainMenuConfirmationScreen = true;
	}
}

void ACarController::OnPressedYesMainMenu()
{
	if (this == mPauseController)
	{
		if (hasOpenedMainMenuConfirmationScreen)
		{
			UGameManager* gameManager{ Cast<UGameManager>(GetGameInstance()) };

			for (uint32 i{ 1 }; i < static_cast<uint32>(gameManager->GetNumberOfPlayers()); ++i)
			{
				UGameplayStatics::RemovePlayer(gameManager->GetPlayerController(i), true);
			}

			gameManager->LoadLevel(EMaps::MainMenu);
		}
	}
}

void ACarController::OnPressedNoMainMenu()
{
	if (this == mPauseController)
	{
		if (hasOpenedMainMenuConfirmationScreen)
		{
			mPauseMenu->mainMenuConfirmation->SetVisibility(ESlateVisibility::Hidden);
			mPauseMenu->pauseContainer->SetVisibility(ESlateVisibility::Visible);

			mPauseMenu->resumeButton->SetUserFocus(this);

			hasOpenedMainMenuConfirmationScreen = false;
		}
	}
}