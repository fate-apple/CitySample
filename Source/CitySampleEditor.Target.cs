// Copyright Epic Games, Inc. All Rights Reserved.

using EpicGames.Core;
using Microsoft.Extensions.Logging;
using UnrealBuildTool;

public class CitySampleEditorTarget : TargetRules
{
	public CitySampleEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.Add("CitySample");
		ExtraModuleNames.Add("CitySampleEditor");
		ExtraModuleNames.Add("CitySampleAnimGraphRuntime");

		if (Type == TargetType.Editor && Platform.IsInGroup(UnrealPlatformGroup.Linux) && LinuxPlatform.bEnableThreadSanitizer)
		{
			// Escape the path to the file. We might be building on Windows and if so the directory separator must be escaped
			string SanitizerSuppressionsFile = FileReference.Combine(Target.ProjectFile.Directory, "Build", "SanitizerCompiletimeSuppressions.ini").FullName.Replace("\\", "\\\\");
			AdditionalCompilerArguments += $" -fsanitize-blacklist=\"{SanitizerSuppressionsFile}\"";

			Logger.LogInformation($"Using LLVM Sanitizer suppressions from '{SanitizerSuppressionsFile}'");

			string[] TSanDisabledPlugins = 
			{
				"NeuralNetworkInference",
				"RemoteControl",
				"Text3D"
			};

			foreach (string PluginName in TSanDisabledPlugins)
			{
				DisablePlugins.Add(PluginName);
				EnablePlugins.Remove(PluginName);
			}
		}
	}
}
