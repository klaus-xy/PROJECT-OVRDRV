// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaosVehicleWheel.h"
#include "ODWheelFrontBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_OVRDRV_API UODWheelFrontBase : public UChaosVehicleWheel
{
	GENERATED_BODY()

public:
	UODWheelFrontBase();
};
