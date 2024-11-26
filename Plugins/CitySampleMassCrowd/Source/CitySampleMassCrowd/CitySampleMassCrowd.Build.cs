// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CitySampleMassCrowd : ModuleRules
{
	public CitySampleMassCrowd(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
			}
			
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				// Mass core
				"MassEntity",

				// AI/MassAI Plugin Modules
				"MassAIBehavior",
				"MassAIDebug",
				"MassNavigation",
				"MassZoneGraphNavigation",
				
				// AI/MassCrowd Plugin Modules
				"MassCrowd",

				// Runtime/MassGameplay Plugin Modules
				"MassActors",
				"MassCommon",
				"MassGameplayDebug",
				"MassLOD",
				"MassMovement",
				"MassReplication",
				"MassRepresentation",
				"MassSignals",
				"MassSimulation",
				"MassSmartObjects",
				"MassSpawner",
				
				"SmartObjectsModule", // work around until we find a better way to get data from smart object configs
				
				// Misc
				"AnimToTexture",
				"ContextualAnimation",
				"Core",
				"Engine",
				"MotionWarping",
				"DeveloperSettings",
				"StateTreeModule",
				"ZoneGraph",
				"ZoneGraphDebug",
				"MassTraffic",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Slate",
				"SlateCore",
				"GameplayTasks",
				"MassSimulation",
				"RenderCore",
				"RHI"
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
		
		if (Target.bBuildEditor == true)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"UnrealEd",
				}
			);
		}
	}
}
