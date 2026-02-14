// Fill out your copyright notice in the Description page of Project Settings.


#include "ODPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "PROJECT_OVRDRV.h"
#include "Blueprint/UserWidget.h"
#include "UI/ODVehicleHUD.h"
#include "UI/ODUIBase.h"
#include "Vehicles/ODVehiclePawnBase.h"

void AODPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// only spawn UI on local player controllers
	if (IsLocalPlayerController())
	{
		// Create the UI widget and add it to the viewport
		VehicleHUD = CreateWidget<UODVehicleHUD>(this, VehicleHUDClass);
		if (VehicleHUD)
		{
			VehicleHUD->AddToViewport();
		}
	}
		
}

void AODPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(VehiclePawn) && IsValid(VehicleHUD))
	{
		VehicleHUD->UpdateSpeed(VehiclePawn->GetCurrentMovementComponent()->GetForwardSpeed());
		VehicleHUD->UpdateRPM(VehiclePawn->GetCurrentMovementComponent()->GetEngineRotationSpeed(), VehiclePawn->GetCurrentMovementComponent()->GetEngineMaxRotationSpeed());
		VehicleHUD->UpdateGear(VehiclePawn->GetCurrentMovementComponent()->GetCurrentGear());
	}

}

void AODPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	VehiclePawn = Cast<AODVehiclePawnBase>(InPawn);
	if (!VehiclePawn)
	{
		UE_LOG(LogPROJECT_OVRDRV, Warning, TEXT("Possessed pawn is not a vehicle pawn."))
	};
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




