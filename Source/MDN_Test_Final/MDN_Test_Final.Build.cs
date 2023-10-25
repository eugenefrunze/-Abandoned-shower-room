// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MDN_Test_Final : ModuleRules
{
	public MDN_Test_Final(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
