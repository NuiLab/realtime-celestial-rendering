// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class celestialdemo : ModuleRules
{
	public celestialdemo(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "RHI", "SkyboxShader", "ShaderCopyHelper" });

        PrivateDependencyModuleNames.AddRange(new string[] {  });

	}
}
