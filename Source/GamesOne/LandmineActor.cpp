// Fill out your copyright notice in the Description page of Project Settings.


#include "LandmineActor.h"

// Sets default values
ALandmineActor::ALandmineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LandmineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Landmine Mesh"));


}

// Called when the game starts or when spawned
void ALandmineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALandmineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

