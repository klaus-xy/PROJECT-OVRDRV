// Copyright Clown Ware Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ODPlayerController.generated.h"

class UODVehicleUIBase;
class UInputMappingContext;


/**
 *  Vehicle Player Controller class
 *  Handles input mapping and user interface
 */
UCLASS(abstract)
class PROJECT_OVRDRV_API AODPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	// ::::::::::::::	🖼️[UI SETUP]🎨  :::::::::::::: //
	
	// HUD UI :::::::::::::: //
	UPROPERTY(EditAnywhere, Category="Vehicle|UI")
	TSubclassOf<UODVehicleUIBase> VehicleHUDClass;

	// Pointer to the UI widget
	UPROPERTY()
	TObjectPtr<UODVehicleUIBase> VehicleHUD;

	// ::::::::::::::	🕹️[INPUT SETUP]🎮  :::::::::::::: //
	// Input Mapping Context to be used for player input //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext* InputMappingContext;
	

protected:
	/** Gameplay initialization */
	virtual void BeginPlay() override;
	
	/** Input setup */
	virtual void SetupInputComponent() override;
	
	

protected:
	/** Pawn setup */
	//virtual void OnPossess(APawn* InPawn) override;
	
};
