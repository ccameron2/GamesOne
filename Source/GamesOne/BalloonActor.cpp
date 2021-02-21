// Fill out your copyright notice in the Description page of Project Settings.


#include "BalloonActor.h"

// Sets default values
ABalloonActor::ABalloonActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Create Balloon mesh and set as root component
	BalloonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Balloon Mesh"));
	SetRootComponent(BalloonMesh);

}

// Called when the game starts or when spawned
void ABalloonActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABalloonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Add upwards force to balloon every tick
	BalloonMesh->AddForce(GetActorUpVector() * ForceAmount * BalloonMesh->GetMass());
}

