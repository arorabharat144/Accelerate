// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadingScreenModule.h"
#include "SlateApplication.h"
#include "LoadingScreenSettings.h"

ULoadingScreenModule::ULoadingScreenModule()
{

}

void ULoadingScreenModule::Startup()
{
	if (!IsRunningDedicatedServer() && FSlateApplication::IsInitialized())
	{
		//const ULoadingScreenSettings* settings{ GetDefault<ULoadingScreenSettings>() };
		settings = NewObject<ULoadingScreenSettings>(this, settingsRef->GetAuthoritativeClass());
		for (const FSoftObjectPath& ref : settings->startupScreen.images)
		{
			ref.TryLoad();
		}
		for (const FSoftObjectPath& ref : settings->defaultScreen.images)
		{
			ref.TryLoad();
		}

		if (IsMoviePlayerEnabled())
		{
			GetMoviePlayer()->OnPrepareLoadingScreen().AddLambda([this]()
			{ 
				ULoadingScreenModule::HandlePrepareLoadingScreen();
			});
		}

		BeginLoadingScreen(settings->startupScreen);
	}
}

void ULoadingScreenModule::Shutdown()
{
	if (!IsRunningDedicatedServer())
	{
		GetMoviePlayer()->OnPrepareLoadingScreen().RemoveAll(this);
	}
}

void ULoadingScreenModule::HandlePrepareLoadingScreen()
{
	const ULoadingScreenSettings* settings{ GetDefault<ULoadingScreenSettings>() };
	BeginLoadingScreen(settings->defaultScreen);
}

void ULoadingScreenModule::BeginLoadingScreen(const FLoadingScreenDescription& screenDescription)
{
	FLoadingScreenAttributes loadingScreen;
	loadingScreen.MinimumLoadingScreenDisplayTime = screenDescription.minimumLoadingScreenDisplayTime;
	loadingScreen.bAutoCompleteWhenLoadingCompletes = screenDescription.autoCompleteWhenLoadingCompletes;
	loadingScreen.bMoviesAreSkippable = screenDescription.moviesAreSkippable;
	loadingScreen.bWaitForManualStop = screenDescription.waitForManualStop;
	loadingScreen.MoviePaths = screenDescription.moviePaths;
	loadingScreen.PlaybackType = screenDescription.playbackType;

	if (screenDescription.showUIOverlay)
	{
		//loadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
	}

	GetMoviePlayer()->SetupLoadingScreen(loadingScreen);
}