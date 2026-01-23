// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PROJECT_OVRDRV : ModuleRules
{
	public PROJECT_OVRDRV(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"ChaosVehicles",
			"PhysicsCore",
			"UMG",
			"Slate"
		});

		PublicIncludePaths.AddRange(new string[] {
			"PROJECT_OVRDRV",
			"PROJECT_OVRDRV/SportsCar",
			"PROJECT_OVRDRV/OffroadCar",
			"PROJECT_OVRDRV/Variant_Offroad",
			"PROJECT_OVRDRV/Variant_TimeTrial",
			"PROJECT_OVRDRV/Variant_TimeTrial/UI"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
