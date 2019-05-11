// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SScaleBox.h"
#include "MoviePlayer.h"

#include "LoadingScreenDescription.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ACCELERATE_API FLoadingScreenDescription
{
	GENERATED_BODY()

	FLoadingScreenDescription();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading")
	float minimumLoadingScreenDisplayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading")
	bool autoCompleteWhenLoadingCompletes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading")
	bool moviesAreSkippable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading")
	bool waitForManualStop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading")
	TEnumAsByte<EMoviePlaybackType> playbackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movies")
	TArray<FString> moviePaths;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	bool showUIOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FText loadingText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images", meta = (AllowedClasses = "Texture2D"))
	TArray<FSoftObjectPath> images;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	TEnumAsByte<EStretch::Type> imageStretch;

};
