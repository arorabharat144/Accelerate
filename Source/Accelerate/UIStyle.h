// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateTypes.h"

/**
 * 
 */
struct MyButtonStyle
{
	FButtonStyle normalStyle;
	FButtonStyle hoveredStyle;
	FButtonStyle pressedStyle;
};

struct MyCarCustomizationButtonStyle
{
	MyButtonStyle leftStyle;
	MyButtonStyle rightStyle;
};

struct MyCheckboxStyle
{
	FCheckBoxStyle uncheckedStyle;
	FCheckBoxStyle uncheckedHoveredStyle;
	FCheckBoxStyle uncheckedPressedStyle;
	FCheckBoxStyle checkedStyle;
	FCheckBoxStyle checkedHoveredStyle;
	FCheckBoxStyle checkedPressedStyle;
};