// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class aei : ModuleRules
{
	public aei(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"GameplayTags",
			"GameplayAbilities",
			"GameplayTasks"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"aei",
			"aei/Variant_Platforming",
			"aei/Variant_Platforming/Animation",
			"aei/Variant_Combat",
			"aei/Variant_Combat/AI",
			"aei/Variant_Combat/Animation",
			"aei/Variant_Combat/Gameplay",
			"aei/Variant_Combat/Interfaces",
			"aei/Variant_Combat/UI",
			"aei/Variant_SideScrolling",
			"aei/Variant_SideScrolling/AI",
			"aei/Variant_SideScrolling/Gameplay",
			"aei/Variant_SideScrolling/Interfaces",
			"aei/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
