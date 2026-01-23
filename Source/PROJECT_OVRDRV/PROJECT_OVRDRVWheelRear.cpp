// Copyright Epic Games, Inc. All Rights Reserved.

#include "PROJECT_OVRDRVWheelRear.h"
#include "UObject/ConstructorHelpers.h"

UPROJECT_OVRDRVWheelRear::UPROJECT_OVRDRVWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}