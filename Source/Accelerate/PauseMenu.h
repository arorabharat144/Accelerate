// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/CanvasPanel.h"

#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class ACCELERATE_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	TArray<UButton*> GetButtons() const;

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "PauseMenu")
	UButton* resumeButton;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "PauseMenu")
	UButton* restartButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "PauseMenu")
	UButton* mainMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "PauseMenu")
	UCanvasPanel* pauseContainer;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "PauseMenu")
	UCanvasPanel* restartConfirmation;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "PauseMenu")
	UCanvasPanel* mainMenuConfirmation;
};
