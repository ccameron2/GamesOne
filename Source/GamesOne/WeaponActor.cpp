// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActor.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh"));
	SetRootComponent(GunMesh);
	GunMesh->SetVisibility(true);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(GunMesh);
	ProjectileSpawnPoint->SetRelativeLocation(FVector(-10.8f, 59.0f, 11.0f));
	
	GunSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Skeletal Mesh"));
	GunSkeletalMesh->SetupAttachment(GunMesh);

}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponActor::OnFire()
{
	UE_LOG(LogTemp, Warning, TEXT("Shots fired!"));

	if (BulletClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		//FVector SpawnLocation = FVector(-10.8f, 59.0f, 11.0f);
		ABulletActor* TempBullet = GetWorld()->SpawnActor<ABulletActor>(BulletClass, SpawnLocation, SpawnRotation);
	}
}

