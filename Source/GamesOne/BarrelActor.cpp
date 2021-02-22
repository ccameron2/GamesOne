// Fill out your copyright notice in the Description page of Project Settings.


#include "BarrelActor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABarrelActor::ABarrelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Create Barrel Mesh and set as root component.
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel Mesh"));
	SetRootComponent(BarrelMesh);
	BarrelMesh->SetSimulatePhysics(true);

	//Create radial force component and attach to barrel mesh
	ForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("Force Component"));
	ForceComp->SetupAttachment(BarrelMesh);


}

void ABarrelActor::Explode()
{
	//Spawn Explosion actor
	AExplosion* Explosion;
	Explosion = GetWorld()->SpawnActor<AExplosion>(ExplosionClass, this->GetActorLocation() + FVector(0,0,80), this->GetActorRotation());
	//Play explosion sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
	//Fire radial impulse
	ForceComp->FireImpulse();
	//Destroy actor
	Destroy();
}

// Called when the game starts or when spawned
void ABarrelActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABarrelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Add actor rotation for consistent spin speed
	FRotator Rotator = FRotator(0.0f, 1.0f, 0.0f);
	AddActorLocalRotation(Rotator);

}