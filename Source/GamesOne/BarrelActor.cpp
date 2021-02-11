// Fill out your copyright notice in the Description page of Project Settings.


#include "BarrelActor.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ABarrelActor::ABarrelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel Mesh"));
	BarrelMesh->SetupAttachment(RootComponent);
	BarrelMesh->SetSimulatePhysics(true);

	ForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("Force Component"));
	ForceComp->SetupAttachment(BarrelMesh);


}

void ABarrelActor::Explode()
{
	ForceComp->FireImpulse();
	Destroy();
}

// Called when the game starts or when spawned
void ABarrelActor::BeginPlay()
{
	Super::BeginPlay();
	BarrelMesh->AddTorqueInRadians(FVector(0.0f, 0.0f, 100.0f) * ForceAmount * BarrelMesh->GetMass());

}

// Called every frame
void ABarrelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BarrelMesh->AddForce(GetActorUpVector() * ForceAmount * BarrelMesh->GetMass());
}

