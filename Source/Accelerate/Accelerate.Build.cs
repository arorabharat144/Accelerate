// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Accelerate : ModuleRules
{
	public Accelerate(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "PhysXVehicles", "HeadMountedDisplay", "UMG", "Slate", "SlateCore", "MoviePlayer" });

		PublicDefinitions.Add("HMD_MODULE_INCLUDED=1");
	}
}
