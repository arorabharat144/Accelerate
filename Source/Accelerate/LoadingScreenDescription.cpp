// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadingScreenDescription.h"

#define LOCTEXT_NAMESPACE "LoadingScreen"

FLoadingScreenDescription::FLoadingScreenDescription() :
	minimumLoadingScreenDisplayTime{ -1.0f },
	autoCompleteWhenLoadingCompletes{ true },
	moviesAreSkippable{ true },
	waitForManualStop{ false },
	showUIOverlay{ true },
	loadingText{ LOCTEXT("Loading", "LOADING") },
	imageStretch{ EStretch::ScaleToFit }
{

}
