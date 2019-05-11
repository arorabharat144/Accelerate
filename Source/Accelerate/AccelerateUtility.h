// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "CoreUObject/Public/UObject/Class.h"

class ACCELERATE_API AccelerateUtility
{
public:

	template<class EnumType, class EnumFormat>
	static FString GetStringFromEnum(FString enumName, EnumType enumValue);

	template<class EnumType, class EnumFormat>
	static EnumType GetEnumFromString(FString enumName, FString enumString);

	static FString RemoveWhiteSpaces(FString str);

	static int32 GetEnumSize(FString enumName);
};

template<class EnumType, class EnumFormat>
FString AccelerateUtility::GetStringFromEnum(FString enumName, EnumType enumValue)
{
	const UEnum* en{ FindObject<UEnum>(ANY_PACKAGE, *enumName, true) };

	verifyf(en, TEXT("Invalid - are you sure enum uses UENUM() macro?"));
	
	return en->GetNameStringByIndex(static_cast<EnumFormat>(enumValue));
}

template<class EnumType, class EnumFormat>
EnumType AccelerateUtility::GetEnumFromString(FString enumName, FString enumString)
{
	const UEnum* en{ FindObject<UEnum>(ANY_PACKAGE, *enumName, true) };

	verifyf(en, TEXT("Invalid - are you sure enum uses UENUM() macro?"));

	int32 index{ en->GetIndexByName(*enumString) };
	return static_cast<EnumType>(static_cast<EnumFormat>(index));
}