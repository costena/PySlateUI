using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Desktop)]
public class PySlateTarget : TargetRules
{
	public PySlateTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Program;
		bShouldCompileAsDLL = true;
		LinkType = TargetLinkType.Monolithic;
		LaunchModuleName = "PySlate";
		SolutionDirectory = "ExternalPrograms";
		DefaultBuildSettings = BuildSettingsVersion.V2;
		
		// Lean and mean
		bBuildDeveloperTools = false;

		// Currently this app is not linking against the engine, so we'll compile out references from Core to the rest of the engine
		bCompileAgainstEngine = false;
		bCompileAgainstCoreUObject = true;

		bUseLoggingInShipping = true;
		bCompileWithPluginSupport = false;
		bUseChecksInShipping = true;

		bHasExports = false;
	}
}
