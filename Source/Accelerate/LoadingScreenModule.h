// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoadingScreenModuleInterface.h"

#include "LoadingScreenModule.generated.h"

struct FLoadingScreenDescription;

UCLASS(Blueprintable)
class ACCELERATE_API ULoadingScreenModule : public UObject
{
public:
	GENERATED_BODY()

	ULoadingScreenModule();

	void Startup();
	void Shutdown();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ULoadingScreenSettings> settingsRef;

	ULoadingScreenSettings* settings;

private:
	void HandlePrepareLoadingScreen();

	void BeginLoadingScreen(const FLoadingScreenDescription& screenDescription);
};
