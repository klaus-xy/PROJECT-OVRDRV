// Copyright Epic Games, Inc. All Rights Reserved.

#include "PROJECT_OVRDRVWheelFront.h"
#include "UObject/ConstructorHelpers.h"

UPROJECT_OVRDRVWheelFront::UPROJECT_OVRDRVWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}