// Fill out your copyright notice in the Description page of Project Settings.


#include "ODWheelFrontBase.h"

UODWheelFrontBase::UODWheelFrontBase()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}
