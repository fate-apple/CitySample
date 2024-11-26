// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MassTraffic : ModuleRules
{
	public MassTraffic(ReadOnlyTargetRules Target) : base(Target)
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
				"MassRepresentation",
				"MassSpawner",
				
				// Misc
				"AIModule",
				"Core",
				"Engine",
				"NetCore",
				"StateTreeModule",
				"ZoneGraph",
				"AnimToTexture",
				"ChaosVehicles",
				"ChaosVehiclesCore",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// Runtime/MassGameplay Plugin Modules
				"MassMovement",
				"MassReplication",
				"MassSimulation",
				
				// Misc
				"CoreUObject",
				"GameplayTasks",
				"PointCloud",
				"RHI",
				"RenderCore",
				"Slate",
				"SlateCore",
				"PhysicsCore",
				"Chaos",
				"ChaosCore",
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
