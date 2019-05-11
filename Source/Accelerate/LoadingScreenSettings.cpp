// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadingScreenSettings.h"
#include "ConstructorHelpers.h"
#include "Engine/Font.h"

ULoadingScreenSettings::ULoadingScreenSettings(const FObjectInitializer& Initializer) :
	Super{ Initializer },
	tipWrapAt{ 1000.0f }
{
	if (!IsRunningDedicatedServer())
	{
		static ConstructorHelpers::FObjectFinder<UFont> robotoFontObj{ TEXT("/Engine/EngineFonts/Roboto") };
		tipFont = FSlateFontInfo{ robotoFontObj.Object, 20, FName{"Normal"} };
		loadingFont = FSlateFontInfo{ robotoFontObj.Object, 32, FName{"Bold"} };
	}
}