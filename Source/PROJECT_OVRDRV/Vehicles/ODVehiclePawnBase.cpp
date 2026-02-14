// Fill out your copyright notice in the Description page of Project Settings.


#include "ODVehiclePawnBase.h"

#include "ChaosWheeledVehicleMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
AODVehiclePawnBase::AODVehiclePawnBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	//	----------------	[CONSTRUCT VEHICLE CHASSIS MESH]	------------------	//
	MainBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Body"));
	MainBodyMesh->SetupAttachment(GetMesh());

	//	----------------	[CONSTRUCT VEHICLE WHEELS]	------------------	//
	// Create and Attach Wheel Static Mesh to a bone/socket on the parent Skeletal Mesh
	
	// [WHEEL FL]
	WheelFL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel_FL"));
	WheelFL->SetupAttachment(GetMesh(), FName("Phys_Wheel_FL"));
	
	// [WHEEL FR]
	WheelFR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel_FR"));
	WheelFR->SetupAttachment(GetMesh(), FName("Phys_Wheel_FR")); 
	
	// [WHEEL BL]
	WheelBL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel_BL"));
	WheelBL->SetupAttachment(GetMesh(), FName("Phys_Wheel_BL"));

	// [WHEEL BR]
	WheelBR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel_BR"));
	WheelBR->SetupAttachment(GetMesh(), FName("Phys_Wheel_BR"));

	
	
	//	----------------	[CONSTRUCT CAMERA SETUP]	------------------	//
	// [INIT REAR CAMERA]
	// Rear Spring Arm Setup
	RearSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Rear Spring Arm"));	  // Create Spring arm 
	RearSpringArm->SetupAttachment(GetMesh());	// Attach spring arm to parent skeletal mesh
	RearSpringArm->TargetArmLength = 600.0f;
	RearSpringArm->SocketOffset.Z = 150.0f;
	RearSpringArm->bDoCollisionTest = false;
	RearSpringArm->bInheritPitch = true;
	RearSpringArm->bInheritRoll = false;
	RearSpringArm->bEnableCameraLag = true;
	RearSpringArm->CameraLagSpeed = 20.0f;
	RearSpringArm->bEnableCameraRotationLag = true;
	RearSpringArm->CameraRotationLagSpeed = 4.0f;
	RearSpringArm->CameraLagMaxDistance = 400.0f;

	// Rear Camera Setup
	RearCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Front Camera"));
	RearCamera->SetupAttachment(RearSpringArm);

	bCanResetCamera = true;
	CameraResetDelay = 1.5f;
	CameraResetCurveLookupDuration = 2.0f;
	CameraResetSpeed = 5.0f;
	CameraLookSensitivity = 1.0f;
	

	//	----------------	[SETUP VEHICLE PHYSICS]	------------------	//
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(FName("Vehicle"));

	//	----------------	[SETUP CHAOS VEHICLE MOVEMENT COMPONENT]	------------------	//
	CurrentVehicleMovementComponent = CastChecked<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement());
	if (CurrentVehicleMovementComponent)
	{
		CurrentVehicleMovementComponent->bEnableCenterOfMassOverride = true;
		CurrentVehicleMovementComponent->CenterOfMassOverride = FVector::ZeroVector;
	}

	
	

	//	----------------	[SETUP ALL VEHICLES DATA TABLE]	------------------	//
	TryFindAllVehiclesDataTable();

	if (CurrentVehicleMovementComponent)
	{
		BindVehicleConfig();
	}
	
	VehicleID = VehicleData.VehicleID;
	
}


// Called when the game starts or when spawned
void AODVehiclePawnBase::BeginPlay()
{
	Super::BeginPlay();

	// Initialize Vehicle Data (If found in Data Table)
	InitVehicleConfig();
	
}

// Called every frame
void AODVehiclePawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanResetCamera)
	{
		HandleCameraReset(DeltaTime);
	}
}

// Called to bind functionality to input
void AODVehiclePawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Steering 
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &AODVehiclePawnBase::Steer);
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Completed, this, &AODVehiclePawnBase::Steer);

		// Throttle 
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &AODVehiclePawnBase::Throttle);
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &AODVehiclePawnBase::Throttle);

		// Brake
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &AODVehiclePawnBase::Brake);
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &AODVehiclePawnBase::Brake);
		//EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Started, this, &AODVehiclePawnBase::StartBrake);
		//EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &AODVehiclePawnBase::StopBrake);

		// HandBrake
		EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Started, this, &AODVehiclePawnBase::HandBrake);
		EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Completed, this, &AODVehiclePawnBase::HandBrake);

		// Look around 
		EnhancedInputComponent->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &AODVehiclePawnBase::LookAround);
		EnhancedInputComponent->BindAction(LookAroundAction, ETriggerEvent::Completed, this, &AODVehiclePawnBase::ResetCamera);
		// Reset Camera on complete

	}
}

void AODVehiclePawnBase::TryFindAllVehiclesDataTable()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> VehiclesDataTableFinder(TEXT("/Game/VehicleTemplate/Data/DT_ODVehicleDataTable"));

	if (VehiclesDataTableFinder.Succeeded())
	{
		VehiclesDataTable = VehiclesDataTableFinder.Object;
		UE_LOG(LogTemp, Log, TEXT("✔️ Found and Assigned Vehicle DataTable at: /Game/VehicleTemplate/Data/DT_ODVehicleDataTable"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("❌ Failed to find Vehicle DataTable at: /Game/VehicleTemplate/Data/DT_ODVehicleDataTable"));
	}
}

void AODVehiclePawnBase::InitVehicleConfig()
{
	// Find vehicle data from Data Table using Vehicle ID. Assign to Vehicle Data if found. Else, throw an error.
	if (VehiclesDataTable)
	{
		FODVehicleData* RowData = VehiclesDataTable->FindRow<FODVehicleData>(VehicleID, TEXT("ℹ Vehicle Data Init"));
		if (RowData)
		{
			VehicleData = *RowData;
			BindVehicleConfig();
			CurrentVehicleMovementComponent->RecreatePhysicsState();

			UE_LOG(LogTemp, Log, TEXT("✔️ VEHICLE DATA FOUND AND APPLIED"));
			GEngine->AddOnScreenDebugMessage(0,5,FColor::Green,FString::Printf(
			TEXT("✅ Vehicle Data Assigned: %s (ID:: %s)"),
			*VehicleData.VehicleName.ToString(),
			*VehicleData.VehicleID.ToString()
			));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("❌ VEHICLE DATA NOT FOUND"));
			GEngine->AddOnScreenDebugMessage(0,5,FColor::Red,FString::Printf(
			TEXT("❌ Vehicle Row Data Not Found in DataTable:: %s"),
			*VehicleID.ToString()));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(0,5,FColor::Red,TEXT("No Vehicle Data Table Found!"));
	}

}

void AODVehiclePawnBase::BindVehicleConfig()
{
	// Binds found vehicle row data to a corresponding movement component.
	
	// Bind chassis setup
	GetCurrentMovementComponent()->Mass = VehicleData.ChassisData.Mass;
	GetCurrentMovementComponent()->ChassisHeight = VehicleData.ChassisData.ChassisHeight;
	GetCurrentMovementComponent()->DragCoefficient = VehicleData.ChassisData.DragCoefficient;
	
	// Bind engine setup
	GetCurrentMovementComponent()->EngineSetup = VehicleData.EngineData;

	// Bind differential setup
	GetCurrentMovementComponent()->DifferentialSetup = VehicleData.DifferentialData;
	
	// Bind transmission setup
	GetCurrentMovementComponent()->TransmissionSetup = VehicleData.TransmissionData;

	// Bind steering setup
	GetCurrentMovementComponent()->SteeringSetup = VehicleData.SteeringData;
}

//	::::::::::::  INPUT METHODS :::::::::::	//
void AODVehiclePawnBase::Steer(const FInputActionValue& Value)
{
	HandleSteering(Value.Get<float>());
}

void AODVehiclePawnBase::Throttle(const FInputActionValue& Value)
{
	HandleThrottle(Value.Get<float>());
}

void AODVehiclePawnBase::Brake(const FInputActionValue& Value)
{
	HandleBrake(Value.Get<float>());
}

void AODVehiclePawnBase::HandBrake(const FInputActionValue& Value)
{
	HandleHandBrake(Value.Get<bool>());
	GEngine->AddOnScreenDebugMessage(0,2,FColor::Green,FString::Printf(
			TEXT("HANDBRAKE:: %s"),
			Value.Get<bool>() ? TEXT("ENGAGED") : TEXT("RELEASED")));
}

void AODVehiclePawnBase::LookAround(const FInputActionValue& Value)
{
	bCanResetCamera = false;
	HandleLookAround(Value.Get<float>());
}

void AODVehiclePawnBase::ResetCamera()
{	
	// Start Reset Countdown Timer & Handle Reset when countdown reaches zero
	GetWorldTimerManager().SetTimer(CameraResetStartTimer,this,&AODVehiclePawnBase::BeginCameraReset,CameraResetDelay,false);	
}

//	::::::::::::  METHOD IMPLEMENTATIONS :::::::::::	//
void AODVehiclePawnBase::HandleSteering(float Value)
{
	// Steering logic
	CurrentVehicleMovementComponent->SetSteeringInput(Value);
}

void AODVehiclePawnBase::HandleThrottle(float Value)
{
	// Throttle logic
	CurrentVehicleMovementComponent->SetThrottleInput(Value);
}

void AODVehiclePawnBase::HandleBrake(float Value)
{
	// Braking logic
	CurrentVehicleMovementComponent->SetBrakeInput(Value);
}

void AODVehiclePawnBase::HandleHandBrake(bool Value)
{
	// Handbrake logic
	CurrentVehicleMovementComponent->SetHandbrakeInput(Value);
}

void AODVehiclePawnBase::HandleLookAround(float YawDelta)
{
	// Look around logic
	FreeLookRotation.Yaw += YawDelta * CameraLookSensitivity;

	// todo:: Add optional clamp later. (esp for pitch)
	
	RearSpringArm->SetRelativeRotation(FreeLookRotation);
}

void AODVehiclePawnBase::BeginCameraReset()
{
	CameraResetElapsedTime = 0.0f;
	bCanResetCamera = true;
}


// Reset camera logic
void AODVehiclePawnBase::HandleCameraReset(float DeltaTime)
{
	if (CameraResetSpeedCurve != nullptr)
	{
		CameraResetElapsedTime += DeltaTime;
		float Alpha = FMath::Clamp(CameraResetElapsedTime / CameraResetCurveLookupDuration,0.0f,1.0f);
		
		FreeLookRotation = FMath::RInterpTo(FreeLookRotation, FRotator::ZeroRotator, DeltaTime, CameraResetSpeedCurve->GetFloatValue(Alpha)*CameraResetSpeed);
	}
	else
	{
		FreeLookRotation = FMath::RInterpTo(FreeLookRotation, FRotator::ZeroRotator, DeltaTime, CameraResetSpeed);
		GEngine->AddOnScreenDebugMessage(0,5,FColor::Red,TEXT("No Camera Reset Speed Curve Found! Using Linear Interpolation for camera reset"));
	}
		RearSpringArm->SetRelativeRotation(FreeLookRotation);

	if (FreeLookRotation.IsNearlyZero(0.01))
	{
		bCanResetCamera = false;
		FreeLookRotation = FRotator::ZeroRotator;
		RearSpringArm->SetRelativeRotation(FreeLookRotation);
		CameraResetElapsedTime = 0.0f;
	}
}


