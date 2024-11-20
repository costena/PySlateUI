using System.IO;
using UnrealBuildTool;

public class PySlate : ModuleRules
{
	public PySlate(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDefinitions.Add("USE_PYTHON=1");
		bEnableExceptions = true;
		bUseRTTI = Target.Platform == UnrealTargetPlatform.Win64;
		PublicIncludePaths.Add(Path.Combine(EngineDirectory, "Source/Runtime/Launch/Public"));
		PrivateIncludePaths.Add(Path.Combine(EngineDirectory, "Source/Runtime/Launch/Private"));
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"AppFramework",
			"Core",
			"CoreUObject",
			"ApplicationCore",
			"Slate",
			"SlateCore",
			"StandaloneRenderer",
			"DesktopPlatform",
			"Projects",
			"Json",
			"Python311",
		});
		
	}
}