// Fill out your copyright notice in the Description page of Project Settings.

#include "PauseMenu.h"

TArray<UButton*> UPauseMenu::GetButtons() const
{
	TArray<UButton*> buttons;

	buttons.Add(resumeButton);
	buttons.Add(restartButton);
	buttons.Add(mainMenuButton);

	return buttons;
}