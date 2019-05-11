// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SCompoundWidget.h"
#include "LoadingScreenSettings.h"
#include "Engine/Public/Slate/DeferredCleanupSlateBrush.h"
//#include "LoadingScreenWidget.generated.h"

class UTexture2D;
class UGameManager;

struct FLoadingScreenBrush : public FSlateDynamicImageBrush, public FGCObject
{
	FLoadingScreenBrush(UTexture2D* inTexture, const FVector2D& inImageSize, const FName inImagePath) :
		FSlateDynamicImageBrush{ inTexture, inImageSize, inImagePath }
	{

	}

	virtual void AddReferencedObjects(FReferenceCollector& collector) override
	{
		UObject* object{ GetResourceObject() };
		if (object != nullptr)
		{
			collector.AddReferencedObject(object);
		}
	}
};

class ACCELERATE_API SLoadingScreenWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLoadingScreenWidget) {}

	SLATE_END_ARGS()

	void Construct(const FArguments& inArguments, const FLoadingScreenDescription& description, const UGameManager* gameManager);

	virtual void Tick(const FGeometry& allottedGeometry, const double inCurrentTime, const float inDeltaTime) override;

private:
	float GetDPIScale() const;

private:
	TSharedPtr<FLoadingScreenBrush> mLoadingScreenBrush;
	float mLastComputedDPIScale;
};
