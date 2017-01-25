namespace UnrealBuildTool.Rules
{
	public class SkyboxShader : ModuleRules
	{
		public SkyboxShader(TargetInfo Target)
        {
            PrivateIncludePaths.AddRange(
                new string[] {
					"SkyboxShader/Private"
				}
                );

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
                    "Engine",
                    "RenderCore",
                    "ShaderCore",
                    "RHI"
				}
				);
		}
	}
}
