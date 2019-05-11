// Fill out your copyright notice in the Description page of Project Settings.

#include "SuspensionComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values for this component's properties
USuspensionComponent::USuspensionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USuspensionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USuspensionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USuspensionComponent::CastRay(FHitResult& hit)
{
	FRotator componentRotation = GetComponentRotation();
	auto quat = componentRotation.Quaternion();

	FVector origin = GetComponentLocation();
	FVector EndLocation = origin + (-UKismetMathLibrary::GetUpVector(componentRotation) * SuspensionLength);

	FCollisionQueryParams CollisionParams;


	bool isHitting = GetWorld()->LineTraceSingleByChannel(hit, origin, EndLocation,
		ECollisionChannel::ECC_GameTraceChannel1, CollisionParams);


	if (isHitting)
	{
		DrawDebugLine(GetWorld(), origin, EndLocation, FColor::Green, false, 0.0f, 0, 1.f);
		DrawDebugBox(GetWorld(), hit.ImpactPoint, FVector(0.5f, 0.5f, 0.5f), FColor::Green, false, 0.0f, 000, 1.0f);
	}
	else
	{
		DrawDebugLine(GetWorld(), origin, EndLocation, FColor::Red, false, 0.0f, 0, 1.f);
		DrawDebugBox(GetWorld(), EndLocation, FVector(0.5f, 0.5f, 0.5f), FColor::Red, false, 0.0f, 000, 1.0f);
	}

	return isHitting;
}
