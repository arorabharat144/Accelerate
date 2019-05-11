// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"

/**
 * 
 */
class ACCELERATE_API ILoadingScreenModule : public IModuleInterface
{
public:
	static inline ILoadingScreenModule& Get()
	{
		return FModuleManager::LoadModuleChecked<ILoadingScreenModule>("LoadingScreen");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("LoadingScreen");
	}
};
