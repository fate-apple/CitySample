// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "MassProcessor.h"
#include "CitySampleDebugVisualization.generated.h"


UCLASS()
class CITYSAMPLEMASSCROWD_API UCitySampleDebugVisProcessor : public UMassProcessor
{
	GENERATED_BODY()
public:
	UCitySampleDebugVisProcessor();
	virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

protected:
	UPROPERTY(EditAnywhere)
	float AgentRadiusToUse = 30.f;

	FMassEntityQuery EntityQuery;
};
