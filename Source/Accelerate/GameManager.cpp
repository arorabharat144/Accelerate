// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "Ticker.h"
#include "PrimaryWeaponTypes.h"
#include "Engine.h"

#include "ModeTypeContainers.h"

#include "Maps.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "AccelerateUtility.h"
#include "GameFramework/GameUserSettings.h"
//#include "LoadingScreenModule.h"

//#include "LoadingScreenWidget.h"
#include "Geometry.h"

UGameManager::UGameManager()
{
	
}

void UGameManager::Init()
{
	mTickDelegateHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UGameManager::Tick));

	Super::Init();

	//mLoadingScreenModule = NewObject<ULoadingScreenModule>(this, loadingScreenModuleRef->GetAuthoritativeClass());
	//mLoadingScreenModule->Startup();

	//SAssignNew(mLoadingScreenWidget, SLoadingScreenWidget, mLoadingScreenModule->settings->defaultScreen, this);
	//mLoadingScreenWidget->Construct(mLoadingScreenModule->settings->defaultScreen);
}

void UGameManager::Shutdown()
{
	FTicker::GetCoreTicker().RemoveTicker(mTickDelegateHandle);

	Super::Shutdown();

	//mLoadingScreenModule->Shutdown();
}

bool UGameManager::Tick(float DeltaTime)
{
	//mLoadingScreenWidget->Tick(, 0.0, DeltaTime);

	return true;
}

const TArray<AAcceleratePlayer*> UGameManager::GetPlayers() const
{
	return mPlayers;
}

int32 UGameManager::GetNumberOfPlayers() const
{
	return mNumberOfPlayers;
}

const int32 UGameManager::GetMaximumPlayerCount()
{
	return 4;
}

AAcceleratePlayer* UGameManager::GetPlayer(int32 index) const
{
	return mPlayers[index];
}

void UGameManager::SetNumberOfPlayers(int32 numberOfPlayers)
{
	mNumberOfPlayers = numberOfPlayers;
}

APlayerController* UGameManager::GetPlayerController(int32 index) const
{
	return mPlayerControllers[index];
}

void UGameManager::SetSelectedPrimaryWeapon(int32 index, EPrimaryOffensiveWeaponTypes selectedWeapon)
{
	mSelectedPrimaryOffensiveWeapons.Add(index, selectedWeapon);
}

const TMap<int32, EPrimaryOffensiveWeaponTypes>& UGameManager::GetSelectedPrimaryOffensiveWeapons() const
{
	return mSelectedPrimaryOffensiveWeapons;
}

EMaps UGameManager::GetCurrentMap() const
{
	return mCurrentMap;
}

void UGameManager::SetCurrentMap(EMaps currentMap)
{
	mCurrentMap = currentMap;
}

TSharedPtr<ModeType> UGameManager::GetSelectedMode() const
{
	return mCurrentModeType;
}

void UGameManager::LoadLevel(EMaps map)
{
	FString mapString{ "MAP_" };
	mapString += AccelerateUtility::GetStringFromEnum<EMaps, uint8>({ "EMaps" }, map);
	UGameplayStatics::OpenLevel(GetWorld(), *mapString);

	mCurrentMap = map;
}

void UGameManager::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UGameManager::Reset()
{

}

void UGameManager::ToggleFullscreen(bool status)
{
	
	UGameUserSettings* gameSettings{ GEngine ? GEngine->GetGameUserSettings() : nullptr };

	if(!gameSettings)
	{
		return;
	}

	if (true == status)
	{
		gameSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	}
	else
	{
		gameSettings->SetFullscreenMode(EWindowMode::Windowed);
	}

	gameSettings->ApplySettings(true);
}
//
//ULoadingScreenModule* UGameManager::GetLoadingScreenModule() const
//{
//	return mLoadingScreenModule;
//}