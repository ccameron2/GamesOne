// Fill out your copyright notice in the Description page of Project Settings.


#include "BalloonActor.h"

// Sets default values
ABalloonActor::ABalloonActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BalloonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Balloon Mesh"));
	BalloonMesh->SetupAttachment(RootComponent);

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
	BalloonMesh->AddForce(GetActorUpVector() * ForceAmount * BalloonMesh->GetMass());
}

