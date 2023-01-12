// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class test_muti_4 : ModuleRules
{
	public test_muti_4(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
