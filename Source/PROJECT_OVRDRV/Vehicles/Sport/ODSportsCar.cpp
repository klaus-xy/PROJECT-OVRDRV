// Fill out your copyright notice in the Description page of Project Settings.


#include "ODSportsCar.h"

#include "ChaosWheeledVehicleMovementComponent.h"
#include "ODSportWheelFront.h"
#include "ODSportWheelRear.h"



// Sets default values
AODSportsCar::AODSportsCar()
{
	//	----------------	🛞[CHAOS PHYSICS WHEELS SETUP]🛻		------------ //
	// VehicleData.ChassisData.Mass = 200.0f;
	GetCurrentMovementComponent()->WheelSetups.SetNum(4);
	
	GetCurrentMovementComponent()->WheelSetups[0].WheelClass = UODSportWheelFront::StaticClass();
	GetCurrentMovementComponent()->WheelSetups[0].BoneName = FName("Phys_Wheel_FL");
	GetCurrentMovementComponent()->WheelSetups[0].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetCurrentMovementComponent()->WheelSetups[1].WheelClass = UODSportWheelFront::StaticClass();
	GetCurrentMovementComponent()->WheelSetups[1].BoneName = FName("Phys_Wheel_FR");
	GetCurrentMovementComponent()->WheelSetups[1].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetCurrentMovementComponent()->WheelSetups[2].WheelClass = UODSportWheelRear::StaticClass();
	GetCurrentMovementComponent()->WheelSetups[2].BoneName = FName("Phys_Wheel_BL");
	GetCurrentMovementComponent()->WheelSetups[2].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetCurrentMovementComponent()->WheelSetups[3].WheelClass = UODSportWheelRear::StaticClass();
	GetCurrentMovementComponent()->WheelSetups[3].BoneName = FName("Phys_Wheel_BR");
	GetCurrentMovementComponent()->WheelSetups[3].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

}




