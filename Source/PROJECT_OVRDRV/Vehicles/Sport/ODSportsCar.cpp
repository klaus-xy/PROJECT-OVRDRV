// Fill out your copyright notice in the Description page of Project Settings.


#include "ODSportsCar.h"

#include "ChaosWheeledVehicleMovementComponent.h"
#include "ODSportsWheelFront.h"
#include "ODSportWheelRear.h"



// Sets default values
AODSportsCar::AODSportsCar()
{
	// todo:: setup default values for sport cars
	// todo:: default vehicle id based on vehicle type 
	
	//	----------------	🛞[CHAOS PHYSICS WHEELS SETUP]🛻		------------ //
	GetCurrentMovementComponent()->ChassisHeight = 144.0f;
	GetCurrentMovementComponent()->DragCoefficient = 0.31f;
	
	GetCurrentMovementComponent()->WheelSetups.SetNum(4);
	
	GetCurrentMovementComponent()->WheelSetups[0].WheelClass = UODSportsWheelFront::StaticClass();
	GetCurrentMovementComponent()->WheelSetups[0].BoneName = FName("Phys_Wheel_FL");
	GetCurrentMovementComponent()->WheelSetups[0].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetCurrentMovementComponent()->WheelSetups[1].WheelClass = UODSportsWheelFront::StaticClass();
	GetCurrentMovementComponent()->WheelSetups[1].BoneName = FName("Phys_Wheel_FR");
	GetCurrentMovementComponent()->WheelSetups[1].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetCurrentMovementComponent()->WheelSetups[2].WheelClass = UODSportWheelRear::StaticClass();
	GetCurrentMovementComponent()->WheelSetups[2].BoneName = FName("Phys_Wheel_BL");
	GetCurrentMovementComponent()->WheelSetups[2].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetCurrentMovementComponent()->WheelSetups[3].WheelClass = UODSportWheelRear::StaticClass();
	GetCurrentMovementComponent()->WheelSetups[3].BoneName = FName("Phys_Wheel_BR");
	GetCurrentMovementComponent()->WheelSetups[3].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	//VehicleData.EngineData.MaxRPM = 62545.0f;
}




