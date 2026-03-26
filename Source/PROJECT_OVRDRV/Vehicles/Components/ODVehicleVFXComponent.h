// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "ODVehicleVFXComponent.generated.h"


class UChaosWheeledVehicleMovementComponent;
class AODVehiclePawnBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_OVRDRV_API UODVehicleVFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UODVehicleVFXComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// ::::::::::::: NIAGARA VFX SYSTEMS ::::::::::::: //
	// Holds references to Niagara Systems used for vehicle VFX. These are set in the editor and used to spawn Niagara Components at runtime.
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),  Category = "Vehicle VFX")
	TObjectPtr<UNiagaraSystem> WheelSmokeSystem;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),  Category = "Vehicle VFX")
	TObjectPtr<UNiagaraSystem> TrailSystem;

	// add other systems here...
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),  Category = "Vehicle VFX")
	bool bDebugAllVfxSystems;
	// :::::::::::::::::::	OVR//DRV	:::::::::::::::::::: //

	// Controls maximum smoke particles spawn rate (multiplied by a base value - the normalized slip/skid magnitude)
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),  Category = "Vehicle VFX | Speed Trails")
	//float WheelSmokeIntensityMultiplier;
	
	// This value sets the slip/skid magnitude where the min particles should start spawning (e.g if set to 500, spawn rate starts increasing after slip/skid magnitude of 500. Value remains at 0 before magnitude of 500. Value of 0 automatically uses the wheel slip/skid threshold)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),  Category = "Vehicle VFX | Smoke VFX")
	float ThresholdSmokeMagnitude;
	
	// This value sets the slip/skid magnitude where the max particles should be spawned (e.g if set to 2000, spawn rate is at max value at magnitude of 2000 and remains the same with values over 2000)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),  Category = "Vehicle VFX | Smoke VFX")
	float MaxSmokeMagnitude;

	// This value sets the max spawn rate for smoke particles
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),  Category = "Vehicle VFX | Smoke VFX")
	float MaxSmokeIntensity;
	
	// Speed threshold for spawning trail VFX (in MPH)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),  Category = "Vehicle VFX | Speed Trails")
	float TrailThresholdSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),  Category = "Vehicle VFX | Speed Trails")
	float TrailBaseSpawnRate; 
	
	// ::::::::::::: NIAGARA VFX COMPONENTS ::::::::::::: //
	// Holds references to dynamically spawned Niagara VFX Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),  Category = "Vehicle VFX")
	TArray<TObjectPtr<UNiagaraComponent>> SpawnedWheelSmokeComponents;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),  Category = "Vehicle VFX")
	TArray<TObjectPtr<UNiagaraComponent>> SpawnedTrailComponents;

	// add other components here...	
	// :::::::::::::::::::	OVR//DRV	:::::::::::::::::::: //

	// ::::::::::::: NIAGARA SYSTEMS ::::::::::::: //
	// Socket names for each wheel to attach the smoke VFX to
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),  Category = "Vehicle VFX")
	TArray<FName> WheelSocketNames; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),  Category = "Vehicle VFX")
	TArray<FName> TrailSocketNames;

	// add other s here...
	// :::::::::::::::::::	OVR//DRV	:::::::::::::::::::: //
	
	
private:
	// Reference to the owning vehicle pawn
	UPROPERTY()
	TObjectPtr<AODVehiclePawnBase> OwningVehiclePawn;
	
	// Vehicle Movement Component reference
	TObjectPtr<UChaosWheeledVehicleMovementComponent> VehicleMovementComponent;
	
	// Initialize all VFX components.
	void InitializeAllVehicleVfxComponents();

	// Initialize the wheel VFX components.
	void InitializeWheelVfx();

	// Initialize Trail VFX (trails that spawn at specific speed threshold)
	void InitializeTrailVfx();

	void UpdateAllVfx();
	void UpdateWheelVfx();
	void UpdateTrailVfx();

	// Debug all VFX components currently attached to the vehicle
	void DebugAllVehicleVfx();

	// Debug wheel vfx
	void DebugWheelVfx();
	// Visualize trail socket locations
	void DebugTrailVfx();
};

