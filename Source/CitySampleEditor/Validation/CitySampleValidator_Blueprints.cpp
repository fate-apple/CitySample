// Copyright Epic Games, Inc. All Rights Reserved.

#include "CitySampleValidator_Blueprints.h"
#include "Engine/Blueprint.h"
#include "Blueprint/BlueprintSupport.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "CitySampleEditor/CitySampleEditor.h"
#include "CitySampleValidator_Load.h"

#define LOCTEXT_NAMESPACE "CitySampleValidator"

bool UCitySampleValidator_Blueprints::bShouldLoadReferencingBlueprintsInEditor = false;

UCitySampleValidator_Blueprints::UCitySampleValidator_Blueprints()
	: Super()
{
}

void UCitySampleValidator_Blueprints::SetShouldLoadReferencingBlueprintsInEditor(bool bNewShouldLoadReferencingBlueprintsInEditor)
{
	bShouldLoadReferencingBlueprintsInEditor = bNewShouldLoadReferencingBlueprintsInEditor;
}

bool UCitySampleValidator_Blueprints::CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const
{
	return Super::CanValidateAsset_Implementation(InAssetData, InAsset, InContext) && (InAsset ? InAsset->IsA(UBlueprint::StaticClass()) : false);
}

EDataValidationResult UCitySampleValidator_Blueprints::ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& Context)
{
	UBlueprint* Blueprint = Cast<UBlueprint>(InAsset);
	check(Blueprint);

	if (IsRunningCommandlet() || bShouldLoadReferencingBlueprintsInEditor)
	{
		// For non-dataonly blueprints, also load and check all directly referencing non-data-only blueprints, as changes may have caused them to fail to compile
		if (!FBlueprintEditorUtils::IsDataOnlyBlueprint(Blueprint))
		{
			FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
			IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

			TSet<FName> AllHardReferencers;

			TArray<FName> PackagesToProcess;
			PackagesToProcess.Add(Blueprint->GetOutermost()->GetFName());

			do
			{
				TArray<FName> NextPackagesToProcess;
				for (FName PackageToProcess : PackagesToProcess)
				{
					TArray<FName> HardReferencers;
					AssetRegistry.GetReferencers(PackageToProcess, HardReferencers, UE::AssetRegistry::EDependencyCategory::Package, UE::AssetRegistry::EDependencyQuery::Hard);
					for (FName HardReferencer : HardReferencers)
					{
						if (!AllHardReferencers.Contains(HardReferencer))
						{
							AllHardReferencers.Add(HardReferencer);
							TArray<FAssetData> RefAssets;
							AssetRegistry.GetAssetsByPackageName(HardReferencer, RefAssets, true);
							for (const FAssetData& RefData : RefAssets)
							{
								if (RefData.IsRedirector())
								{
									NextPackagesToProcess.Add(RefData.PackageName);
									break;
								}
							}
						}
					}
				}
				PackagesToProcess = MoveTemp(NextPackagesToProcess);
			} while (PackagesToProcess.Num() > 0);

			for (FName HardReferencer : AllHardReferencers)
			{
				FString HardReferencerStr = HardReferencer.ToString();
				if (!IsInUncookedFolder(HardReferencerStr) && !IsInTestMapsFolder(HardReferencerStr))
				{
					TArray<FAssetData> ReferencerAssets;
					AssetRegistry.GetAssetsByPackageName(HardReferencer, ReferencerAssets, true);
					for (const FAssetData& ReferencerAssetData : ReferencerAssets)
					{
						// Skip levelscript BPs... for now
						if ((ReferencerAssetData.PackageFlags & PKG_ContainsMap) == 0)
						{
							bool bIsDataOnlyBP = false;
							if (ReferencerAssetData.GetTagValue<bool>(FBlueprintTags::IsDataOnly, bIsDataOnlyBP))
							{
								if (!bIsDataOnlyBP)
								{
									UE_LOG(LogCitySampleEditor, Display, TEXT("    Loading referencing non-dataonly blueprint %s"), *HardReferencerStr);

									TArray<FString> WarningsAndErrors;
									if (UCitySampleValidator_Load::GetLoadWarningsAndErrorsForPackage(HardReferencerStr, WarningsAndErrors))
									{
										for (const FString& WarningOrError : WarningsAndErrors)
										{
											AssetFails(InAsset, FText::FromString(WarningOrError));
										}
									}
									break;
								}
							}
						}
					}
				}
			}
		}
	}

	if (GetValidationResult() != EDataValidationResult::Invalid)
	{
		AssetPasses(InAsset);
	}

	return GetValidationResult();
}

#undef LOCTEXT_NAMESPACE