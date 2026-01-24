// Fill out your copyright notice in the Description page of Project Settings.


#include "ODPlayerController.h"

#include "EnhancedInputSubsystems.h"

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


