// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomDestructibleActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACustomDestructibleActor::ACustomDestructibleActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ACustomDestructibleActor::BeginPlay()
{
	Super::BeginPlay();

	//Add dynamic delegate for fracture event
	OnActorFracture.AddDynamic(this, &ACustomDestructibleActor::OnFracture);
}

// Called every frame
void ACustomDestructibleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACustomDestructibleActor::OnFracture(const FVector& HitPoint, const FVector& HitDirection)
{
	UE_LOG(LogTemp, Warning, TEXT("Shattered"));
	AAmmoActor* AmmoActor = GetWorld()->SpawnActor<AAmmoActor>(AmmoClass, this->GetActorLocation(), this->GetActorRotation());
}

