// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "ODVehicleData.generated.h"

/** Vehicle data structure */


USTRUCT(BlueprintType)
struct FODVehicleData : public FTableRowBase
{
	GENERATED_BODY()
	
	FODVehicleData()
	{
		InitDefaults();
	}

public:
	// IDENTITY DATA
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Identity")
	FName VehicleID;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Identity")
	FText VehicleName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Identity")
	FText Manufacturer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Identity")
	int32 ModelYear;
	
	// ENGINE DATA
	UPROPERTY(EditAnywhere, Category = "MechanicalSetup")
	FVehicleEngineConfig EngineData;

	// DIFFERENTIAL DATA 
	UPROPERTY(EditAnywhere, Category = "MechanicalSetup")
	FVehicleDifferentialConfig DifferentialData;

	// TRANSMISSION DATA
	UPROPERTY(EditAnywhere, Category = "MechanicalSetup")
	FVehicleTransmissionConfig TransmissionData;

	// STEERING DATA
	UPROPERTY(EditAnywhere, Category = "MechanicalSetup")
	FVehicleSteeringConfig SteeringData;

	
	void InitDefaults()
	{
    	VehicleID = TEXT("OVRDRV000");
    	VehicleName = FText::FromString(TEXT("VISION GT"));
    	Manufacturer = FText::FromString(TEXT("117 Industries"));
    	ModelYear = 2026;
	}
};

