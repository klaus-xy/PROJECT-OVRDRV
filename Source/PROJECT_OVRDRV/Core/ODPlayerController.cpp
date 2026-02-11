// Fill out your copyright notice in the Description page of Project Settings.


#include "ODPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "UI/ODVehicleUIBase.h"

void AODPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// only spawn UI on local player controllers
	if (IsLocalPlayerController())
	{
		// Create the UI widget and add it to the viewport
		VehicleHUD = CreateWidget<UODVehicleUIBase>(this, VehicleHUDClass);
		if (VehicleHUD)
		{
			VehicleHUD->AddToViewport();
		}
	}
		
}

void AODPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
				Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}


