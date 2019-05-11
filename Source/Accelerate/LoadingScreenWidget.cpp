// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadingScreenWidget.h"

#include "SScaleBox.h"
#include "SImage.h"
#include "SSpacer.h"
#include "SOverlay.h"
#include "SBoxPanel.h"
#include "STextBlock.h"
#include "SBorder.h"
#include "SSafeZone.h"
#include "SThrobber.h"
#include "SDPIScaler.h"
#include "Engine/Texture2D.h"
#include "Engine/UserInterfaceSettings.h"

#include "Engine.h"
#include "GameManager.h"
#include "LoadingScreenModule.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

//#define LOCTEXT_NAMESPACE "SLoadingScreenWidget"

void SLoadingScreenWidget::Construct(const FArguments& inArguments, const FLoadingScreenDescription& description, const UGameManager* gameManager)
{
	mLastComputedDPIScale = 1.0f;

	//const ULoadingScreenSettings* settings{ gameManager->GetLoadingScreenModule()->settings };
	const ULoadingScreenSettings* settings{ GetDefault<ULoadingScreenSettings>() };

	const FSlateFontInfo& tipFont{ settings->tipFont };
	const FSlateFontInfo& loadingFont{ settings->loadingFont };

	TSharedRef<SOverlay> root{ SNew(SOverlay) };

	if (description.images.Num() > 0)
	{
		int32 imageIndex{ FMath::RandRange(0, description.images.Num() - 1) };
		const FSoftObjectPath& imageAsset{ description.images[imageIndex] };
		UObject* imageObject{ imageAsset.TryLoad() };

		if (UTexture2D* loadingImage{ Cast<UTexture2D>(imageObject) })
		{
			FVector2D size{ FVector2D{static_cast<float>(loadingImage->GetSizeX()), static_cast<float>(loadingImage->GetSizeY())} };
			
			mLoadingScreenBrush = MakeShareable(new FLoadingScreenBrush{ loadingImage, size, FName{ *imageAsset.ToString() } });

			root->AddSlot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SScaleBox)
					.Stretch(description.imageStretch)
					[
						SNew(SImage)
						.Image(mLoadingScreenBrush.Get())
					]
				];
		}

		TSharedRef<SWidget> tipWidget{ SNullWidget::NullWidget };
		if (settings->tips.Num() > 0)
		{
			int32 tipIndex = FMath::RandRange(0, settings->tips.Num() - 1);

			tipWidget = SNew(STextBlock)
				.WrapTextAt(settings->tipWrapAt)
				.Font(tipFont)
				.Text(settings->tips[tipIndex]);
		}

		root->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Bottom)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.BorderBackgroundColor(FLinearColor{0.0f, 0.0f, 0.0f, 0.75f})
				.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
				[
					SNew(SSafeZone)
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Bottom)
					.IsTitleSafe(true)
					[
						SNew(SDPIScaler)
						.DPIScale(this, & SLoadingScreenWidget::GetDPIScale)
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot()
							.Padding(FMargin{25.0f, 0.0f, 0.0f, 0.0f})
							.VAlign(VAlign_Center)
							.AutoWidth()
							[
								SNew(SCircularThrobber)
								.Radius((loadingFont.Size * 96.0f/72.0f) * 0.5f)
							]
							+ SHorizontalBox::Slot()
							.Padding(FMargin{40.0f, 0.0f, 0.0f, 0.0f})
							.AutoWidth()
							.VAlign(VAlign_Center)
							[
								SNew(STextBlock)
								.Text(description.loadingText)
								.Font(loadingFont)
							]
							+ SHorizontalBox::Slot()
							.FillWidth(1)
							.HAlign(HAlign_Fill)
							[
								SNew(SSpacer)
								.Size(FVector2D{ 1.0f, 1.0f })
							]
							+ SHorizontalBox::Slot()
							.AutoWidth()
							.HAlign(HAlign_Right)
							.VAlign(VAlign_Center)
							.Padding(FMargin{10.0f})
							[
								tipWidget
							]
						]
					]
				]
			];

		ChildSlot
		[
			root
		];
	}
}

void SLoadingScreenWidget::Tick(const FGeometry& allottedGeometry, const double inCurrentTime, const float inDeltaTime)
{
	const FVector2D& localSize{ allottedGeometry.GetLocalSize() };
	FIntPoint size{ static_cast<int32>(localSize.X), static_cast<int32>(localSize.Y) };
	const float newScale{ GetDefault<UUserInterfaceSettings>()->GetDPIScaleBasedOnSize(size) };

	if (newScale != mLastComputedDPIScale)
	{
		mLastComputedDPIScale = newScale;
		SlatePrepass(1.0f);
	}
}

float SLoadingScreenWidget::GetDPIScale() const
{
	return mLastComputedDPIScale;
}

//#undef LOCTEXT_NAMESPACE