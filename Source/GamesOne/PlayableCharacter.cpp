// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableCharacter.h"
#include "BarrelActor.h"
#include "EnemyAIController.h"
#include "CustomPlayerController.h"
#include "CustomDestructibleActor.h"
#include "ShootableActor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/Gameplaystatics.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set static mesh as root component
	SetRootComponent(PawnMesh);
	// Create spring arm and attach to staticMesh
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));

	// Springarm settings
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->SetRelativeRotation((new FRotator(0.0f, 0.0f, 0.0f))->Quaternion());
	SpringArm->SetRelativeLocation(FVector(-361.0f,-305.0f,113.0f));
	SpringArm->SetupAttachment(PawnMesh);

	//Create Camera and attach to SpringArm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	//Create spawnpoint for placed landmines
	LandmineSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Landmine Spawn Point"));
	LandmineSpawnPoint->SetRelativeLocation(FVector(50.0f, 0.0f, -90.0f));

	//Create grenade spawn point
	DamagingActorSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Damaging Actor Spawn Point"));
	DamagingActorSpawnPoint->SetRelativeLocation(FVector(0.0f, 20.0f, 90.0f));

	//Create Raycasting cast point for enemy characters
	RaycastingCastPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RaycastingPoint"));
	RaycastingCastPoint->SetRelativeLocation(FVector(32.0f, 16.0f, 70.0f));

	//Create Map spring arm and camera and attach to pawn mesh
	MapArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Map Arm"));
	MapArm->SetupAttachment(PawnMesh);

	MapCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Map Camera"));
	MapCamera->SetupAttachment(MapArm);

	//Possess player 0
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Spawn weapon actor and attach to right hand socket.
	WeaponActor = GetWorld()->SpawnActor<AWeaponActor>(WeaponActorClass, this->GetActorLocation(), this->GetActorRotation());
	FName fnWeaponSocket = TEXT("hand_rSocket");
	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget,true);
	WeaponActor->AttachToComponent(GetMesh(), rules, fnWeaponSocket);

	//Get reference to current game mode.
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


int APlayableCharacter::GetPoints()
{
	return GameModeRef->GetPoints();
}

void APlayableCharacter::MoveForward(float AxisValue)
{
	//Move character forwards
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayableCharacter::Strafe(float AxisValue)
{
	//Strafe character left and right
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void APlayableCharacter::Turn(float AxisValue)
{
	//Turn character left and right
	AddControllerYawInput(AxisValue);
}

void APlayableCharacter::LookUp(float AxisValue)
{
	//Rotate view up and down
	AddControllerPitchInput(AxisValue);
}

void APlayableCharacter::Fire()
{
	//Get reference to controller of character
	AController* ControllerRef = GetController();

	//Get location of camera 
	FVector CameraLocation;
	FRotator CameraRotation;

	//Get viewpoint of controlled character
	ControllerRef->GetPlayerViewPoint(CameraLocation, CameraRotation);

	//Create raycasting hit variables
	FHitResult Hit;
	bool bDidHit;

	//Call weapon's fire function to spawn empty cartridge and play sound
	WeaponActor->OnFire();

	if (Cast<AEnemyAIController>(ControllerRef))//If enemy is controlling character
	{
		//Get reference to player pawn
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		//Get location of raycasting end point
		FVector End = RaycastingCastPoint->GetComponentLocation() + RaycastingCastPoint->GetComponentRotation().Vector() * CastRange;
		//Set focus to playerpawn
		Cast<AEnemyAIController>(ControllerRef)->SetFocus(PlayerPawn);
		//Raycast from raycasting point
		bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, RaycastingCastPoint->GetComponentLocation(), End, ECC_Visibility);
	}
	else
	{
		//Get location of raycasting end point
		FVector End = CameraLocation + CameraRotation.Vector() * CastRange;
		//Raycast from point of view
		bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, End, ECC_Visibility);
	}

	if (bDidHit)//if raycast hits something
	{ 

		if (Hit.GetActor() != nullptr)
		{
			//Output name of hit actor to log
			UE_LOG(LogTemp, Warning, TEXT("Hit Something: %s"), *Hit.GetActor()->GetName()); 

			//Get root component of hit actor
			UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(Hit.GetActor()->GetRootComponent());

			if (Cast<ABarrelActor>(Hit.GetActor()))//If hit a barrel
			{
				//Call barrel's explode function
				Cast<ABarrelActor>(Hit.GetActor())->Explode();
			}
			else if (Cast<APlayableCharacter>(Hit.GetActor()))//If hit a character
			{
				//Apply damage to the character
				UGameplayStatics::ApplyDamage(Hit.GetActor(), BulletDamage, GetInstigatorController(), this, UDamageType::StaticClass());
			}
			else if (Cast<AShootableActor>(Hit.GetActor()))
			{
				//If hit a storage crate
				RootComp->AddImpulse(CameraRotation.Vector() * impulseForce * RootComp->GetMass());
			}

		}
		else
		{
			//Output successful hit to log
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
		//Spawn landmine actor at landmine spawn point
		ALandmineActor* LandmineActor;
		LandmineActor = GetWorld()->SpawnActor<ALandmineActor>(LandmineActorClass, LandmineSpawnPoint->GetComponentLocation(), LandmineSpawnPoint->GetComponentRotation());
		LandmineActor->SetOwner(this);
		//Scale actor by 0.2
		LandmineActor->SetActorScale3D(FVector(0.2f, 0.2f, 0.2f));
	}
}

void APlayableCharacter::DamagingActor()
{
	if (DamagingActorClass)
	{
		//spawn grenade at grenade spawn point 
		ADamagingActor* DamagingActor;
		DamagingActor = GetWorld()->SpawnActor<ADamagingActor>(DamagingActorClass, DamagingActorSpawnPoint->GetComponentLocation(), DamagingActorSpawnPoint->GetComponentRotation());
		DamagingActor->SetOwner(this);
		//Scale actor by 1.5
		DamagingActor->SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
		
	}
}



float APlayableCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Take Damage"));
	if (HealthPoints - DamageAmount > 0) //If player would not die from taking damage
	{
		//Play hit sound
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());
		//Remove health points
		HealthPoints -= DamageAmount;
	}
	else
	{
		//Get controller of dead character
		AController* PlayerController = GetController();
		if (Cast<AEnemyAIController>(PlayerController))//If controller is enemy AI
		{
			//Score a point
			GameModeRef->ScorePoint();
		}		
		this->Destroy();//Destroy dead character
		WeaponActor->Destroy();//Call weapon's destroy function
		if (Cast<ACustomPlayerController>(PlayerController))// If controller is player controller
		{
			GameModeRef->GameOver(false);//Set gameover to lose condition
		}
	}
	return 0.0f;
}

