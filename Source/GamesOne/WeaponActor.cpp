// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create weapon mesh and set as root component
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh"));
	SetRootComponent(GunMesh);
	//Set mesh visibility to true
	GunMesh->SetVisibility(true);

	//Create spawn point for bullet casing and attach to weapon mesh
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(GunMesh);
	ProjectileSpawnPoint->SetRelativeLocation(FVector(-10.8f, 59.0f, 11.0f));
	
	//Create skeletal mesh component and attach to gun mesh
	GunSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Skeletal Mesh"));
	GunSkeletalMesh->SetupAttachment(GunMesh);

}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponActor::OnFire()
{
	UE_LOG(LogTemp, Warning, TEXT("Shots fired!"));

	if (BulletClass)
	{
		//Get location and rotation of spawn point
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		//Spawn empty casing at spawn point
		ABulletActor* TempBullet = GetWorld()->SpawnActor<ABulletActor>(BulletClass, SpawnLocation, SpawnRotation);
		//Play gunshot sound
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), GunshotSound, GetActorLocation(), 0.3);
	
	}
}

