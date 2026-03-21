// Fill out your copyright notice in the Description page of Project Settings.


#include "ODVehicleVFXComponent.h"
#include "Vehicles/ODVehiclePawnBase.h"


// Sets default values for this component's properties
UODVehicleVFXComponent::UODVehicleVFXComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	WheelSocketNames.SetNum(4);
	WheelSocketNames[0] = "Phys_Wheel_BL";
	WheelSocketNames[1] = "Phys_Wheel_BR";
	WheelSocketNames[2] = "Phys_Wheel_FL";
	WheelSocketNames[3] = "Phys_Wheel_FR";

	TrailSocketNames.SetNum(2);
	TrailSocketNames[0] = FName("Trail_BL");
	TrailSocketNames[1] = FName("Trail_BR");

	TrailThresholdSpeed = 50.0f;
	TrailBaseSpawnRate = 20.0f;
}


// Called when the game starts
void UODVehicleVFXComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	InitializeAllVehicleVfxComponents();
}


// Called every frame
void UODVehicleVFXComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// Update all VFX components
	if (VehicleMovementComponent)
	{
		UpdateAllVfx();
	}
	
	
	if (bDebugAllVfxSystems)
	{
		DebugAllVehicleVfx();
	}
}

void UODVehicleVFXComponent::InitializeAllVehicleVfxComponents()
{
	// Get the owner pawn and cast it to the base vehicle pawn class
	if (AODVehiclePawnBase* VehiclePawn = Cast<AODVehiclePawnBase>(GetOwner()))
	{
		// Store a reference to the owning vehicle pawn
		OwningVehiclePawn = VehiclePawn;
		// Store a reference to the vehicle's movement component
		VehicleMovementComponent = VehiclePawn->GetCurrentMovementComponent();
	}
	else
	{
		// If the cast fails, log a warning and return early
		UE_LOG(LogTemp, Warning, TEXT("VehicleVFXComponent is attached to an actor that is not a AODVehiclePawnBase. VFX may not function correctly."));
		return;
	}
	
	InitializeWheelVfx();
	InitializeTrailVfx();

	// Initialize other vehicle VFX components here (e.g., exhaust, spoiler trails etc.)

	GEngine->AddOnScreenDebugMessage(1,5,FColor::Magenta,TEXT("ALL VEHICLE VFX COMPONENTS INITIALIZED SUCCESSFULLY"));
}

void UODVehicleVFXComponent::InitializeWheelVfx()
{
	// Wheel VFX initialization logic here. For example, you could set up particle systems for tire smoke, or decals for skid marks.
	int8 WheelNum = VehicleMovementComponent->GetNumWheels();
	for (int8 i = 0; i < WheelNum; i++)
	{
		UNiagaraComponent* NewWheelSmokeVfx = UNiagaraFunctionLibrary::SpawnSystemAttached(
			WheelSmokeSystem,
			OwningVehiclePawn->GetRootComponent(),
			WheelSocketNames[i],
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::KeepRelativeOffset,
			false);

		SpawnedWheelSmokeComponents.Add(NewWheelSmokeVfx);

		// TODO:: Add decal components for skid marks and attach them to the same sockets as the wheel smoke vfx.
		// Activate them based on slip/skid state of the corresponding wheel in the movement component.
	}
}

void UODVehicleVFXComponent::InitializeTrailVfx()
{
	// Attach Niagara components to each trail sockets[]
	int8 TrailsNum = TrailSocketNames.Num();
	
	for (int8 i = 0; i < TrailsNum; i++)
	{
		UNiagaraComponent* NewTrailVfx = UNiagaraFunctionLibrary::SpawnSystemAttached(
			TrailSystem,
			OwningVehiclePawn->GetRootComponent(),
			TrailSocketNames[i],
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::KeepRelativeOffset,
			false);

		SpawnedTrailComponents.Add(NewTrailVfx);
	}
}

void UODVehicleVFXComponent::UpdateAllVfx()
{
	UpdateWheelVfx();
	UpdateTrailVfx();
}

void UODVehicleVFXComponent::UpdateWheelVfx()
{
	// Conditions:: Wheel slip, slip threshold, slip intensity
	// Get Wheels[] -> Wheel States3
	// Set spawned vfx spawn rate
	// int8 WheelNum = VehicleMovementComponent->GetNumWheels();
}

void UODVehicleVFXComponent::UpdateTrailVfx()
{	
	// Get current vehicle speed
	float CurrentSpeed = VehicleMovementComponent->GetForwardSpeedMPH();

	// Check if speed is above threshold and activate trail vfx accordingly
	if (CurrentSpeed > TrailThresholdSpeed)
	{
	// Check and print debug warning if no trail vfx components were spawned and return early
		if (SpawnedTrailComponents.Num() == 0)
		{
			GEngine->AddOnScreenDebugMessage(2,5,FColor::Orange,FString::Printf(
			TEXT("WARNING:: %s :: is trying to spawn Speed Trails but No Trail VFX components were spawned. Check if TrailSocketNames is set up correctly and if the TrailVFXSystem is assigned in Vehicle Blueprint."),
			*OwningVehiclePawn->GetVehicleData().VehicleName.ToString()));
			return;
		}

		// Check and Activate each TrailVFX attached to the vehicle
		for (auto TrailVfx : SpawnedTrailComponents)
		{
			// Check if the trail vfx spawned is valid.
			if (TrailVfx != nullptr)
			{
				TrailVfx->SetFloatParameter(TEXT("SpawnRate"), TrailBaseSpawnRate);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(2,5,FColor::Orange,TEXT("Trail VFX System is NULL. Make sure a VFX system has been assigned in the vehicle blueprints."));
			}
		}
	}
	else
	{
		for (auto TrailVfx : SpawnedTrailComponents)
		{
			// Check if the trail vfx spawned is valid.
			if (TrailVfx != nullptr)
			{
				TrailVfx->SetFloatParameter(TEXT("SpawnRate"), 0);
			}
		}
	}
}

void UODVehicleVFXComponent::DebugAllVehicleVfx()
{
	DebugWheelVfx();
	DebugTrailVfx();	
}

void UODVehicleVFXComponent::DebugWheelVfx()
{
	for (auto SocketName : WheelSocketNames)
	{
		DrawDebugSphere(GetWorld(),OwningVehiclePawn->GetRootComponent()->GetSocketLocation(SocketName),20,12,FColor::Cyan);
	}
}

void UODVehicleVFXComponent::DebugTrailVfx()
{
		for (auto SocketName : TrailSocketNames)
		{
			DrawDebugSphere(GetWorld(),OwningVehiclePawn->GetRootComponent()->GetSocketLocation(SocketName),14,12,FColor::Yellow);
		}
}





