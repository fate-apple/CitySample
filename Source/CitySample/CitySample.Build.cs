// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CitySample : ModuleRules
{
	public CitySample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "HeadMountedDisplay",
            "Json",
            "PhysicsCore",
            "ChaosVehiclesCore",
            "StateTreeModule",
            "HoverDrone",
            "HairStrandsCore",
            "EnhancedInput",
            "GameplayTags",
            "MotionWarping",
            "ContextualAnimation",
			"Media",
			"MediaUtils",
			"MediaAssets",
			"AudioMixer",
			"GeometryCollectionEngine",
			"Gauntlet",
			"MassTraffic",
			"MassZoneGraphNavigation",
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Niagara",
			"CinematicCamera",
			"Foliage",
			"Slate",
			"SlateCore",
			"NetCore",
			"AnimToTexture",
			"ModularGameplay",
			"OnlineSubsystem",
			"OnlineSubsystemUtils",
			"NetworkPrediction",
			"ZoneGraph",
			"AnimGraphRuntime",
			"CitySampleMassCrowd",
			"DeveloperSettings",
			"RenderCore",
			"MoviePlayer",
			"StreamingPauseRendering",
	
			// AI/AISupport Plugin Modules
			"AISupportModule",

			// Mass core
			"MassEntity",

			// AI/MassAI Plugin Modules
			"MassAIBehavior",
			"MassAIDebug",
			
			// AI/MassCrowd Plugin Modules
			"MassCrowd",

			// Runtime/MassGameplay Plugin Modules
			"MassActors",
			"MassCommon",
			"MassGameplayDebug",
			"MassLOD",
			"MassMovement",
			"MassNavigation",
			"MassRepresentation",
			"MassReplication",
			"MassSpawner",
			"MassSimulation",
			"MassSignals",
		});
        

		PrivateIncludePaths.AddRange(new string[]
		{
			"CitySample"
		});

		if(Target.Platform != UnrealTargetPlatform.Linux)
		{
			PrivateDependencyModuleNames.AddRange(new string[]
			{
				"ElectraPlayerRuntime",
				"ElectraPlayerPlugin"
			});
		}

		if (Target.bBuildEditor == true)
		{
			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"UnrealEd",
					"NiagaraEditor",
					"MeshUtilities",
					"Gauntlet"
				}
			);
		}
	}
}
