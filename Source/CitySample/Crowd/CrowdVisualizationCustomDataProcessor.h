// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MassTranslator.h"
#include "MassRepresentationTypes.h"
#include "MassLODSubsystem.h"
#include "CrowdVisualizationCustomDataProcessor.generated.h"

class UMassCrowdRepresentationSubsystem;

UCLASS()
class UMassProcessor_CrowdVisualizationCustomData : public UMassProcessor
{
	GENERATED_BODY()

public:
	UMassProcessor_CrowdVisualizationCustomData();

protected:
	virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;
	virtual void InitializeInternal(UObject&, const TSharedRef<FMassEntityManager>&) override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	void UpdateCrowdCustomData(FMassExecutionContext& Context);

	FMassEntityQuery EntityQuery_Conditional;

	UPROPERTY(Transient)
	UMassLODSubsystem* LODSubsystem;

	UPROPERTY(Transient)
	UWorld* World = nullptr;
};