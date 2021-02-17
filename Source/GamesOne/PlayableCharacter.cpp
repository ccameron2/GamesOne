// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableCharacter.h"
#include "BarrelActor.h"
#include "EnemyAIController.h"
#include "CustomPlayerController.h"
#include "CustomDestructibleActor.h"
#include "ShootableActor.h"

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

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	SpringArm->SetupAttachment(PawnMesh);

	LandmineSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Landmine Spawn Point"));
	LandmineSpawnPoint->SetRelativeLocation(FVector(50.0f, 0.0f, -90.0f));

	DamagingActorSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Damaging Actor Spawn Point"));
	//DamagingActorSpawnPoint->SetRelativeLocation(FVector(0.0f, 20.0f, 90.0f));

	RaycastingCastPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RaycastingPoint"));
	RaycastingCastPoint->SetRelativeLocation(FVector(32.0f, 16.0f, 70.0f));

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	WeaponActor = GetWorld()->SpawnActor<AWeaponActor>(WeaponActorClass, this->GetActorLocation(), this->GetActorRotation());
	FName fnWeaponSocket = TEXT("hand_rSocket");
	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget,true);
	WeaponActor->AttachToComponent(GetMesh(), rules, fnWeaponSocket);

	GameModeRef = Cast<AGamesOneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

}
int APlayableCharacter::GetHealth()
{
	return HealthPoints;
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

int APlayableCharacter::GetPoints()
{
	return GameModeRef->GetPoints();
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

	AController* ControllerRef = GetController();
	FVector CameraLocation;
	FRotator CameraRotation;
	ControllerRef->GetPlayerViewPoint(CameraLocation, CameraRotation);
	float CastRange = 10000.0f;
	FHitResult Hit;
	bool bDidHit;
	if (Cast<AEnemyAIController>(ControllerRef))
	{
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		FVector End = RaycastingCastPoint->GetComponentLocation() + RaycastingCastPoint->GetComponentRotation().Vector() * CastRange;

		Cast<AEnemyAIController>(ControllerRef)->SetFocus(PlayerPawn);
		bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, RaycastingCastPoint->GetComponentLocation(), End, ECC_Visibility);

	}
	else
	{
		FVector End = CameraLocation + CameraRotation.Vector() * CastRange;
		bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, End, ECC_Visibility);
	}
	float impulseForce = 1000.0f;

	if (bDidHit)
	{ 

		if (Hit.GetActor() != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Something: %s"), *Hit.GetActor()->GetName());
			UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(Hit.GetActor()->GetRootComponent());
			if (Cast<ABarrelActor>(Hit.GetActor()))
			{	
				//RootComp->AddImpulse(CameraRotation.Vector() * impulseForce * RootComp->GetMass());
				Cast<ABarrelActor>(Hit.GetActor())->Explode();
			}
			else if (Cast<ACustomDestructibleActor>(Hit.GetActor()))
			{
				UGameplayStatics::ApplyDamage(Hit.GetActor(), BulletDamage, GetInstigatorController(), this, UDamageType::StaticClass());
			}
			else if (Cast<APlayableCharacter>(Hit.GetActor()))
			{
				UGameplayStatics::ApplyDamage(Hit.GetActor(), BulletDamage, GetInstigatorController(), this, UDamageType::StaticClass());
			}
			else if (Cast<AShootableActor>(Hit.GetActor()))
			{
				RootComp->AddImpulse(CameraRotation.Vector() * impulseForce * RootComp->GetMass());
			}
			else
			{
				//Do nothing
			}


		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Something"));
		}
		



	}
	else
	{ 
		UE_LOG(LogTemp, Warning, TEXT("Missed")); 
	}
}


void APlayableCharacter::LandMine()
{
	if (LandmineActorClass)
	{
		ALandmineActor* LandmineActor;
		LandmineActor = GetWorld()->SpawnActor<ALandmineActor>(LandmineActorClass, LandmineSpawnPoint->GetComponentLocation(), LandmineSpawnPoint->GetComponentRotation());
		LandmineActor->SetOwner(this);
		LandmineActor->SetActorScale3D(FVector(0.2f, 0.2f, 0.2f));
	}
}

void APlayableCharacter::DamagingActor()
{
	if (DamagingActorClass)
	{
		ADamagingActor* DamagingActor;
		DamagingActor = GetWorld()->SpawnActor<ADamagingActor>(DamagingActorClass, DamagingActorSpawnPoint->GetComponentLocation(), DamagingActorSpawnPoint->GetComponentRotation());
		DamagingActor->SetOwner(this);

		DamagingActor->SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
		
	}
}



float APlayableCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Take Damage"));
	if (HealthPoints > 0)
	{
		HealthPoints -= DamageAmount;
	}
	else
	{
		AController* PlayerController = GetController();
		if (Cast<AEnemyAIController>(PlayerController))
		{
			GameModeRef->ScorePoint();
		}		
		this->Destroy();
		WeaponActor->Destroy();
		if (Cast<ACustomPlayerController>(PlayerController))
		{
			GameModeRef->GameOver(false);
		}
	}
	return 0.0f;
}

