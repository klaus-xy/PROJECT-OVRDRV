// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PROJECT_OVRDRVPawn.h"
#include "PROJECT_OVRDRVSportsCar.generated.h"

/**
 *  Sports car wheeled vehicle implementation
 */
UCLASS(abstract)
class APROJECT_OVRDRVSportsCar : public APROJECT_OVRDRVPawn
{
	GENERATED_BODY()
	
public:

	APROJECT_OVRDRVSportsCar();
};
