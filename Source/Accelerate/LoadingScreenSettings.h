// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateFontInfo.h"
#include "Engine/DeveloperSettings.h"

#include "LoadingScreenDescription.h"

#include "LoadingScreenSettings.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ACCELERATE_API ULoadingScreenSettings : public UObject
{
	GENERATED_BODY()
	
public:
	ULoadingScreenSettings(const FObjectInitializer& Initializer);

	UPROPERTY(EditAnywhere, Category = "Screens")
	FLoadingScreenDescription startupScreen;

	UPROPERTY(EditAnywhere, Category = "Screens")
	FLoadingScreenDescription defaultScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advice")
	FSlateFontInfo tipFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FSlateFontInfo loadingFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advice")
	float tipWrapAt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advice")
	TArray<FText> tips;
};
