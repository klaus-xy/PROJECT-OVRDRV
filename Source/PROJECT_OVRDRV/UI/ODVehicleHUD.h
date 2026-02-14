// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ODUIBase.h"
#include "ODVehicleHUD.generated.h"

/**
 * 
 */
UCLASS(abstract)
class PROJECT_OVRDRV_API UODVehicleHUD : public UODUIBase
{
	GENERATED_BODY()

	// todo:: update methods and events for vehicle hud display (speed, gear, etc.)

protected:
	// Controls the display of speed in Km/h or MPH
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Vehicle")
	bool bIsMPH = false;
	
public:
	// Called to update the speed display
	void UpdateSpeed(float NewSpeed);

	// Called to update the RPM display
	void UpdateRPM(float NewRPM, float MaxRPM);

	// Called to update the gear display
	void UpdateGear(int32 NewGear);
	

protected:
	UFUNCTION(BlueprintImplementableEvent, Category="Vehicle")
	void OnSpeedUpdate(float NewSpeed);

	UFUNCTION(BlueprintImplementableEvent, Category="Vehicle")
	void OnRPMUpdate(float NewRPM, float MaxRPM);
	
	UFUNCTION(BlueprintImplementableEvent, Category="Vehicle")
	void OnGearUpdate(int32 NewGear);
	
};
