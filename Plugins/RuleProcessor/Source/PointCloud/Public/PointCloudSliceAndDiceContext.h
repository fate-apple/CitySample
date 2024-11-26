// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "PointCloudSliceAndDiceRuleInstance.h"
#include "PointCloudSliceAndDiceShared.h"
#include "PointCloudSliceAndDiceReport.h"
#include "PointCloudStats.h"

class UPointCloud;
class UPointCloudView;
class UPointCloudRuleSlot;
class ASliceAndDiceManager;
class USliceAndDiceMapping;

/** This contains information needed to run A ruleset and information generated by the ruleset when executing */
class POINTCLOUD_API FSliceAndDiceContext
{
public:
	/** Builds a context that will hold the data to work on */
	FSliceAndDiceContext(ASliceAndDiceManager* InManager, bool bInIsReportingRun, EPointCloudReportLevel ReportingLevel = EPointCloudReportLevel::Basic);

	/** Set the reporting / execution mode for this context 
	* @param InReportingType Controls if this context should report, execute or both
	*/
	void SetReportingMode(EPointCloudReportMode InMode);

	/** Return the reporting mode for this context 
	* @return The reporting mode
	*/
	EPointCloudReportMode GetReportingMode() const; 

	/* Executes rule to rule instances compilation using the provided mappings */
	bool Compile(const TArray<USliceAndDiceMapping*>& SelectedMappings);

	/* Returns all the root instances that were gathered during compilation */
	TArray<FPointCloudRuleInstancePtr> GetAllRootInstances();

	/* Returns the root instances associated to a specific mapping */
	const TArray<FPointCloudRuleInstancePtr>* GetRootInstances(USliceAndDiceMapping* InMapping) const;

	/* Return a handle to the statistics object */
	TSharedPtr<FPointCloudStats> GetStats();

	struct POINTCLOUD_API FContextInstance
	{
		FContextInstance(UPointCloud* InPointCloud, UWorld* InWorld, FSliceAndDiceContext *InContext)
			: PointCloud(InPointCloud)
			, World(InWorld)
			, Context(InContext)
		{}

		UPointCloud* GetPointCloud() const { return PointCloud; }
		UWorld* GetWorld() const { return World; }

		void EmitInstance(FPointCloudRuleInstancePtr InInstance, const FString &SlotName);
		void ConsumeInstance(FPointCloudRuleInstancePtr InInstance);
		void FinalizeInstance(FPointCloudRuleInstancePtr InLeafInstance);

		TArray<FPointCloudRuleInstancePtr> Roots;

		/** Queries the rule in a given slot, adding support for externalized slots
		*  vs. direct access to Slots member in the Rule.
		* 
		* @param InRule The rule holding the slot we're interested in
		* @param InSlotIndex The index of the slot in the rule
		* 
		* @return Returns the rule in the slot, or the matching external rule if present. Returns null otherwise.
		*/
		UPointCloudRule* GetSlotRule(const UPointCloudRule* InRule, SIZE_T InSlotIndex);

		/** Add/Remove external rules to instance */
		/** Registers an external rule to a given externalized Rule Slot
		*
		* @param InRule The rule to register
		* @param InRuleSlot The rule slot matching the externalized one
		*/
		void AddExternalRule(UPointCloudRule* InRule, UPointCloudRuleSlot* InRuleSlot);

		/** Unregisters an external rule from a given externalized Rule Slot
		*
		* @param InRule The rule to register
		* @param InRuleSlot The rule slot matching the externalized one
		*/
		void RemoveExternalRule(UPointCloudRule* InRule, UPointCloudRuleSlot* InRuleSlot);

	protected:
		/** Returns the registered external rule for a slot, if any */
		UPointCloudRule* GetExternalRule(const UPointCloudRuleSlot* InRuleSlot);

		/** The point cloud to execute the rule set on */
		UPointCloud* PointCloud = nullptr;

		/** The world to execute the rule set on */
		UWorld* World = nullptr;

		/** Current stack of rule instances */
		TArray<FPointCloudRuleInstancePtr> Instances;

		/** Map for externalized rules */
		TMap<FGuid, UPointCloudRule*> ExternalRules;

		/** Pointer to the context that spawned this instance */
		FSliceAndDiceContext* Context;
	};

	UWorld* GetOriginatingWorld() const;

	/** Pointer back to the manager that's built this context */
	ASliceAndDiceManager* Manager;

	/** The instances that the rule will be executed on */
	TArray<FContextInstance> Instances;

	/** Map from Slice and Dice Manager mapping to context instance */
	TMap<USliceAndDiceMapping*, FContextInstance> InstanceMapping;

	/** Property to control if we're reporting or executing or both */
	EPointCloudReportMode ReportingMode = EPointCloudReportMode::Execute;

	FPointCloudSliceAndDiceReport ReportObject;

	/** Statistics Gathering Object */
	TSharedPtr<FPointCloudStats> Stats;
};
