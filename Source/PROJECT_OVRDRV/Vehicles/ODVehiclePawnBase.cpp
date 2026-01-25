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
}

// Called when the game starts or when spawned
void AODVehiclePawnBase::BeginPlay()
{
	Super::BeginPlay();
	
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

