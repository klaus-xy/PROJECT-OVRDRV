// Fill out your copyright notice in the Description page of Project Settings.


#include "ODWheelRearBase.h"

UODWheelRearBase::UODWheelRearBase()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}
