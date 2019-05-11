// Fill out your copyright notice in the Description page of Project Settings.

#include "AccelerateUtility.h"

FString AccelerateUtility::RemoveWhiteSpaces(FString str)
{
	FString strToReturn{ str };

	strToReturn.RemoveSpacesInline();

	return strToReturn;
}

int32 AccelerateUtility::GetEnumSize(FString enumName)
{
	const UEnum* en{ FindObject<UEnum>(ANY_PACKAGE, *enumName, true) };
	int32 enumSize{ -1 };
	if (en)
	{
		enumSize = static_cast<int32>(en->GetMaxEnumValue());
	}

	return enumSize;
}