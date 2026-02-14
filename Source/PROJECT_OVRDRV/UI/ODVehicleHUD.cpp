// Fill out your copyright notice in the Description page of Project Settings.


#include "ODVehicleHUD.h"

void UODVehicleHUD::UpdateSpeed(float NewSpeed)
{
	float FormattedSpeed = FMath::Abs(NewSpeed) * (bIsMPH ? 0.022f : 0.036f);
	OnSpeedUpdate(FormattedSpeed);
}

void UODVehicleHUD::UpdateRPM(float NewRPM, float MaxRPM)
{
	OnRPMUpdate(NewRPM, MaxRPM);
}

void UODVehicleHUD::UpdateGear(int32 NewGear)
{
	OnGearUpdate(NewGear);
}
