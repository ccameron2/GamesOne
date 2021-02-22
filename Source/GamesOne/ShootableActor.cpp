// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootableActor.h"
#include "PhysicsEngine/RadialForceComponent.h"
// Sets default values
AShootableActor::AShootableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create actor mesh and set as root component
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));
	SetRootComponent(ActorMesh);
	ActorMesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AShootableActor::BeginPlay()
{
	Super::BeginPlay();

	//Spin boxes slightly on beginplay
	ActorMesh->AddTorqueInRadians(FVector(0.0f, 0.0f, 100.0f) * ForceAmount * ActorMesh->GetMass());

}

