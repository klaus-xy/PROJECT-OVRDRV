// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "ODVehicleData.generated.h"

/** Vehicle data structure */

USTRUCT()
struct FVehicleChassisConfig
{
	GENERATED_BODY()

	FVehicleChassisConfig()
	{
		InitDefaults();
	}

	UPROPERTY(EditAnywhere, Category = VehicleSetup, meta = (ClampMin = "0.01", UIMin = "0.01"))
	float Mass;

	/**
	 * Enable to override the calculated COM position with your own fixed value - this prevents the vehicle handling changing when the asset changes
	 */
	UPROPERTY(EditAnywhere, Category = VehicleSetup)
	bool bEnableCenterOfMassOverride;

	/**
	 * The center of mass override value, this value overrides the calculated COM and the COM offset value in the mesh is also ignored.
	 */
	UPROPERTY(EditAnywhere, Category = VehicleSetup, meta = (EditCondition = "bEnableCenterOfMassOverride"))
	FVector CenterOfMassOverride;

	/** Chassis width used for drag force computation (cm)*/
	UPROPERTY(EditAnywhere, Category = VehicleSetup, meta = (ClampMin = "0.01", UIMin = "0.01"))
	float ChassisWidth;

	/** Chassis height used for drag force computation (cm)*/
	UPROPERTY(EditAnywhere, Category = VehicleSetup, meta = (ClampMin = "0.01", UIMin = "0.01"))
	float ChassisHeight;

	/** DragCoefficient of the vehicle chassis - force resisting forward motion at speed */
	UPROPERTY(EditAnywhere, Category = VehicleSetup)
	float DragCoefficient;

	/** DownforceCoefficient of the vehicle chassis - force pressing vehicle into ground at speed */
	UPROPERTY(EditAnywhere, Category = VehicleSetup)
	float DownforceCoefficient;

	void InitDefaults()
	{
		bEnableCenterOfMassOverride = true;
		CenterOfMassOverride = FVector::ZeroVector;
		Mass = 1500.0f;
		ChassisWidth = 180.0f;
		ChassisHeight = 140.0f;
		DragCoefficient = 0.3f;
		DownforceCoefficient = 0.3f;		
	}
};

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

	// CHASSIS DATA
	UPROPERTY(EditAnywhere, Category = "MechanicalSetup")
	FVehicleChassisConfig ChassisData;
	
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
    	
    	VehicleName = FText::FromString(TEXT("VISION GT"));
    	Manufacturer = FText::FromString(TEXT("117 Industries"));
    	ModelYear = 2026;
		VehicleID = FName(*FString::Printf(
		  TEXT("%s_%d"),
		  *VehicleName.ToString(),
		  ModelYear
		  ));
	}
};

