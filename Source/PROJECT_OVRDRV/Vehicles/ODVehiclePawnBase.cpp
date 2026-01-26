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
	ChassisMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chassis"));
	ChassisMesh->SetupAttachment(GetMesh());

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
	RearSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Front Spring Arm"));	  // Create Spring arm 
	RearSpringArm->SetupAttachment(GetMesh());	// Attach spring arm to parent skeletal mesh
	RearSpringArm->TargetArmLength = 650.0f;
	RearSpringArm->SocketOffset.Z = 150.0f;
	RearSpringArm->bDoCollisionTest = false;
	//RearSpringArm->bInheritPitch = false;
	//RearSpringArm->bInheritRoll = false;
	//RearSpringArm->bEnableCameraRotationLag = true;
	//RearSpringArm->CameraRotationLagSpeed = 2.0f;
	//RearSpringArm->CameraLagMaxDistance = 50.0f;

	// Rear Camera Setup
	RearCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Front Camera"));
	RearCamera->SetupAttachment(RearSpringArm);

	//	----------------	[SETUP VEHICLE PHYSICS]	------------------	//
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(FName("Vehicle"));

	//	----------------	[SETUP CHAOS VEHICLE MOVEMENT COMPONENT]	------------------	//
	CurrentVehicleMovementComponent = CastChecked<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement());

	

	//	----------------	[SETUP ALL VEHICLES DATA TABLE]	------------------	//
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

	if (CurrentVehicleMovementComponent)
	{
		BindVehicleData();
	}
	
	VehicleID = VehicleData.VehicleID;

	//	----------------	[BIND VEHICLE DATA]	------------------	//
	
}

// Called when the game starts or when spawned
void AODVehiclePawnBase::BeginPlay()
{
	Super::BeginPlay();

	// Initialize Vehicle Data (If found in Data Table)
	InitVehicleData();
	
}

// Called every frame
void AODVehiclePawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AODVehiclePawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Steering 
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &AODVehiclePawnBase::Steering);
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Completed, this, &AODVehiclePawnBase::Steering);

		// Throttle 
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &AODVehiclePawnBase::Throttle);
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &AODVehiclePawnBase::Throttle);

		// Brake
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &AODVehiclePawnBase::Brake);
		//EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Started, this, &AODVehiclePawnBase::StartBrake);
		//EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &AODVehiclePawnBase::StopBrake);

	}
}

void AODVehiclePawnBase::InitVehicleData()
{
	// Find vehicle data from Data Table using Vehicle ID. Assign to Vehicle Data if found. Else, throw an error.
	if (VehiclesDataTable)
	{
		FODVehicleData* RowData = VehiclesDataTable->FindRow<FODVehicleData>(VehicleID, TEXT("ℹ Vehicle Data Init"));
		if (RowData)
		{
			VehicleData = *RowData;
			BindVehicleData();
			
			GEngine->AddOnScreenDebugMessage(0,5,FColor::Green,FString::Printf(
			TEXT("✅ Vehicle Data Assigned: %s (ID:: %s)"),
			*VehicleData.VehicleName.ToString(),
			*VehicleData.VehicleID.ToString()
			));
		}
		else
		{
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

void AODVehiclePawnBase::BindVehicleData()
{
	
	// Bind chassis setup
	GetCurrentMovementComponent()->Mass = VehicleData.ChassisData.Mass;
	GetCurrentMovementComponent()->ChassisHeight = VehicleData.ChassisData.ChassisHeight;
	GetCurrentMovementComponent()->DragCoefficient = VehicleData.ChassisData.DragCoefficient;
	
	// Bind engine setup
	GetCurrentMovementComponent()->EngineSetup.EngineIdleRPM = VehicleData.EngineData.EngineIdleRPM;
	//GetCurrentMovementComponent()->EngineSetup = VehicleData.EngineData;

	// Bind differential setup
	//GetCurrentMovementComponent()->DifferentialSetup = VehicleData.DifferentialData;
	
	// Bind transmission setup
	//GetCurrentMovementComponent()->TransmissionSetup = VehicleData.TransmissionData;

	// Bind steering setup
	//GetCurrentMovementComponent()->SteeringSetup = VehicleData.SteeringData;
}

void AODVehiclePawnBase::Steering(const FInputActionValue& Value)
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

void AODVehiclePawnBase::HandleSteering(float Value)
{
	// Steering logic
}

void AODVehiclePawnBase::HandleThrottle(float Value)
{
	// Throttle logic
	CurrentVehicleMovementComponent->SetThrottleInput(Value);
}

void AODVehiclePawnBase::HandleBrake(float Value)
{
	// Braking logic
}

