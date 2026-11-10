// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Laboratorio_2 : ModuleRules
{
	public Laboratorio_2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
