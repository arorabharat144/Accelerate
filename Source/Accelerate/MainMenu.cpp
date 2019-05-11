// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"

TArray<UButton*> UMainMenu::GetButtons() const
{
	TArray<UButton*> buttons;

	buttons.Add(raceModeButton);
	buttons.Add(battleModeButton);
	buttons.Add(optionsButton);
	buttons.Add(quitButton);
	buttons.Add(raceBackButton);
	buttons.Add(raceButton);
	buttons.Add(videoButton);
	buttons.Add(audioButton);
	buttons.Add(optionsBackButton);
	buttons.Add(yesQuitButton);
	buttons.Add(noQuitButton);
	buttons.Add(displayBackButton);
	buttons.Add(audioBackButton);
	buttons.Add(mapBackButton);
	buttons.Add(mapSpaceButton);

	buttons.Add(p1MLeftArrow);
	buttons.Add(p1MRightArrow);
	buttons.Add(p1CLeftArrow);
	buttons.Add(p1CRightArrow);
	buttons.Add(p1BOLeftArrow);
	buttons.Add(p1BORightArrow);
	buttons.Add(p1BDLeftArrow);
	buttons.Add(p1BDRightArrow);

	buttons.Add(p2MLeftArrow);
	buttons.Add(p2MRightArrow);
	buttons.Add(p2CLeftArrow);
	buttons.Add(p2CRightArrow);
	buttons.Add(p2BOLeftArrow);
	buttons.Add(p2BORightArrow);
	buttons.Add(p2BDLeftArrow);
	buttons.Add(p2BDRightArrow);

	buttons.Add(p3MLeftArrow);
	buttons.Add(p3MRightArrow);
	buttons.Add(p3CLeftArrow);
	buttons.Add(p3CRightArrow);
	buttons.Add(p3BOLeftArrow);
	buttons.Add(p3BORightArrow);
	buttons.Add(p3BDLeftArrow);
	buttons.Add(p3BDRightArrow);

	buttons.Add(p4MLeftArrow);
	buttons.Add(p4MRightArrow);
	buttons.Add(p4CLeftArrow);
	buttons.Add(p4CRightArrow);
	buttons.Add(p4BOLeftArrow);
	buttons.Add(p4BORightArrow);
	buttons.Add(p4BDLeftArrow);
	buttons.Add(p4BDRightArrow);

	return buttons;
}

TArray<UCheckBox*> UMainMenu::GetCheckBoxes() const
{
	TArray<UCheckBox*> checkBoxes;
	checkBoxes.Add(p1Ready);
	checkBoxes.Add(p2Ready);
	checkBoxes.Add(p3Ready);
	checkBoxes.Add(p4Ready);
	checkBoxes.Add(fullScreenCheckBox);

	return checkBoxes;
}

TArray<UMainMenu::CarCustomizationButton> UMainMenu::GetCarCustomizationMenuButtons() const
{
	TArray<CarCustomizationButton> buttons;

	CarCustomizationButton button;
	button.left = p1MLeftArrow;
	button.right = p1MRightArrow;
	buttons.Add(button);
	button.left = p1CLeftArrow;
	button.right = p1CRightArrow;
	buttons.Add(button);
	button.left = p1BOLeftArrow;
	button.right = p1BORightArrow;
	buttons.Add(button);
	button.left = p1BDLeftArrow;
	button.right = p1BDRightArrow;
	buttons.Add(button);

	button.left = p2MLeftArrow;
	button.right = p2MRightArrow;
	buttons.Add(button);
	button.left = p2CLeftArrow;
	button.right = p2CRightArrow;
	buttons.Add(button);
	button.left = p2BOLeftArrow;
	button.right = p2BORightArrow;
	buttons.Add(button);
	button.left = p2BDLeftArrow;
	button.right = p2BDRightArrow;
	buttons.Add(button);

	button.left = p3MLeftArrow;
	button.right = p3MRightArrow;
	buttons.Add(button);
	button.left = p3CLeftArrow;
	button.right = p3CRightArrow;
	buttons.Add(button);
	button.left = p3BOLeftArrow;
	button.right = p3BORightArrow;
	buttons.Add(button);
	button.left = p3BDLeftArrow;
	button.right = p3BDRightArrow;
	buttons.Add(button);

	button.left = p4MLeftArrow;
	button.right = p4MRightArrow;
	buttons.Add(button);
	button.left = p4CLeftArrow;
	button.right = p4CRightArrow;
	buttons.Add(button);
	button.left = p4BOLeftArrow;
	button.right = p4BORightArrow;
	buttons.Add(button);
	button.left = p4BDLeftArrow;
	button.right = p4BDRightArrow;
	buttons.Add(button);

	return buttons;
}