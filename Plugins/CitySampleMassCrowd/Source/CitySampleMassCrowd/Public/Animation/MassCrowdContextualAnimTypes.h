// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/DataAsset.h"

#include "MassCrowdContextualAnimTypes.generated.h"

USTRUCT()
struct FMassCrowdContextualAnimation
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Anim)
	class UContextualAnimSceneAsset* ContextualAnimAsset = nullptr;

	UPROPERTY(EditAnywhere, Category = Anim)
	class UAnimMontage* FallbackMontage = nullptr;
};

USTRUCT()
struct FMassCrowdContextualAnimDescription
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Anim)
	TArray<FMassCrowdContextualAnimation> Anims;

	UPROPERTY(EditAnywhere, Category = Anim)
	FName AlignmentTrack;

	UPROPERTY(EditAnywhere, Category = Anim)
	FName InteractorRole;
};

UCLASS(MinimalAPI, Blueprintable)
class UMassCrowdContextualAnimationDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = Anim, meta = (GetOptions = "CitySampleMassCrowd.MassCrowdAnimationSettings.GetContextualAnimOptions"))
	TMap<FName, FMassCrowdContextualAnimDescription> AnimsMap;
};