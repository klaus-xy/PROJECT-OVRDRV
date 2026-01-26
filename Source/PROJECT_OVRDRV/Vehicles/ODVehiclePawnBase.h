// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Data/ODVehicleData.h"
#include "GameFramework/SpringArmComponent.h"
#include "ODVehiclePawnBase.generated.h"

class UChaosWheeledVehicleMovementComponent;
class UCameraComponent;
struct FInputActionValue;
class UInputAction;

UCLASS(Abstract)
class PROJECT_OVRDRV_API AODVehiclePawnBase : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AODVehiclePawnBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	//	----------------	🩻[CHAOS VEHICLE MOVEMENT COMPONENT SETUP]🛻		------------ //
	TObjectPtr<UChaosWheeledVehicleMovementComponent> CurrentVehicleMovementComponent;
	

	//	----------------	📅[VEHICLE DATA SETUP]🛻		------------ //
	UPROPERTY(EditDefaultsOnly, Category="Vehicle Setup|Data")
	TObjectPtr<UDataTable> VehiclesDataTable; // Todo:: Auto find in project.

	UPROPERTY(EditDefaultsOnly, Category="Vehicle Setup|Data")
	FName VehicleID; // Only editable in blueprints and not instances.

	UPROPERTY()
	FODVehicleData VehicleData;

	// Init Vehicle Data from Data Table
	void InitVehicleData();
	
	// Bind vehicle data to corresponding Chaos Movement Component variables
	void BindVehicleData();
	
public:
	//	----------------	🩻[CHASSIS SETUP]🛻		------------ //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Vehicle Setup|Chassis")
	TObjectPtr<UStaticMeshComponent> ChassisMesh;

	//	----------------	🛞[WHEELS SETUP]🛻		------------ //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Vehicle Setup|Chassis")
	TObjectPtr<UStaticMeshComponent> WheelFR;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Vehicle Setup|Chassis")
	TObjectPtr<UStaticMeshComponent> WheelFL;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Vehicle Setup|Chassis")
	TObjectPtr<UStaticMeshComponent> WheelBR;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Vehicle Setup|Chassis")
	TObjectPtr<UStaticMeshComponent> WheelBL;
	
	//	----------------	🎥[CAMERA SETUP]🎥		------------ //

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Vehicle Setup|Camera")
	TObjectPtr<USpringArmComponent> RearSpringArm;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Vehicle Setup|Camera")
	TObjectPtr<UCameraComponent> RearCamera;
	
	protected:
	//	----------------	[INPUT SETUP]		------------ // 
	// ----		[INPUT ACTIONS]		---- //
	
	//	Steering Action
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* SteeringAction;

	//	Throttle Action
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* ThrottleAction;

	//	Brake Action
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* BrakeAction;

	//	Handbrake Action 
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* HandbrakeAction;

	//	Look Around Action 
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAroundAction;

	//	Toggle Camera Action 
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* ToggleCameraAction;

	//	Reset Vehicle Action 
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* ResetVehicleAction;

	
	// ----		[INPUT CALLBACK FUNCTIONS]		---- //
	
	// Handles steering input 
	void Steering(const FInputActionValue& Value);

	// Handles throttle input
	void Throttle(const FInputActionValue& Value);

	// Handles brake input 
	void Brake(const FInputActionValue& Value);
	
	// ----		[INPUT METHODS]		---- //
	// Handles steering logic
	void HandleSteering(float Value);
	
	// Handles throttle logic
	void HandleThrottle(float Value);

	// Handles brake logic
	void HandleBrake(float Value);

public:
	const TObjectPtr<UChaosWheeledVehicleMovementComponent>& GetCurrentMovementComponent() const {return CurrentVehicleMovementComponent;}
};
