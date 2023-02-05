// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Rath : ModuleRules
{
	public Rath(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",
			//"HoudiniEngine", "HoudiniEngineEditor", "HoudiniEngineRuntime",
			"Slate","SlateCore",
			"GameplayAbilities", "GameplayTags", "GameplayTasks"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			
		});
	}
}
