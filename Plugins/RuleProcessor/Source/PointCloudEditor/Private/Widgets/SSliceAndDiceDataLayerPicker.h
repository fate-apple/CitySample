// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SSliceAndDicePickerWidget.h"

class UDataLayerInstance;

bool GetDataLayerInstance(
	const TSharedPtr<SWidget>& ParentWidget,
	UWorld* InWorld,
	const UDataLayerInstance*& OutDataLayerSelected);
