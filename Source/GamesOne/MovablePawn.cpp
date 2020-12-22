// Fill out your copyright notice in the Description page of Project Settings.


#include "MovablePawn.h"

// Sets default values
AMovablePawn::AMovablePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create Static Mesh
	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube Mesh"));
	SetRootComponent(PawnMesh);

	// Create spring arm and attach to staticMesh
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(PawnMesh);

	// Springarm settings
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->SetRelativeRotation((new FRotator(-30, 0.0f, 0.0f))->Quaternion());
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	Camera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// Initialise CustomMovementComponent
	PawnMovement = CreateDefaultSubobject<UCustomMovementComponent>(TEXT("Pawn Movement"));

}



