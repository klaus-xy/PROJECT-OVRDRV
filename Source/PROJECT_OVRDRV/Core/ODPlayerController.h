// Copyright Clown Ware Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ODPlayerController.generated.h"

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
	// Input Mapping Context to be used for player input //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext* InputMappingContext;

protected:
	/** Input setup */
	virtual void SetupInputComponent() override;
	
	

protected:
	/** Pawn setup */
	//virtual void OnPossess(APawn* InPawn) override;
	
};
