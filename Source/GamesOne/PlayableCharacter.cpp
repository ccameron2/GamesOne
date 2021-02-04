// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableCharacter.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(PawnMesh);
	// Create spring arm and attach to staticMesh
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	

	// Springarm settings
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->SetRelativeRotation((new FRotator(0.0f, 0.0f, 0.0f))->Quaternion());
	SpringArm->SetRelativeLocation(FVector(-361.0f,-305.0f,113.0f));
	SpringArm->SetupAttachment(PawnMesh);

	Camera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	WeaponActor = GetWorld()->SpawnActor<AWeaponActor>(WeaponActorClass, this->GetActorLocation(), this->GetActorRotation());
	FName fnWeaponSocket = TEXT("hand_rSocket");
	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget,true);
	WeaponActor->AttachToComponent(GetMesh(), rules, fnWeaponSocket);
}
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	/*Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move Forwards", this, &APlayableCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Turn", this, &APlayableCharacter::Turn);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &APlayableCharacter::Fire);
	PlayerInputComponent->BindAxis("Strafe", this, &APlayableCharacter::Strafe);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &APlayableCharacter::Jump);
	PlayerInputComponent->BindAxis("Look Up", this, &APlayableCharacter::LookUp);*/
}

void APlayableCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayableCharacter::Strafe(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void APlayableCharacter::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void APlayableCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void APlayableCharacter::Fire()
{
	WeaponActor->OnFire();
	//implement raycasting code here to check if player is hit;
	//implement dealing damage
}
