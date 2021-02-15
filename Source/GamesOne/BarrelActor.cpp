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

	//GetWorld()->GetTimerManager().SetTimer(BarrelTimer, this, &ABarrelActor::TimeUp, TimerDuration, false);
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
}

// Called every frame
void ABarrelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TimerEnd)
	{
		BarrelMesh->AddTorqueInRadians(FVector(0.0f, 0.0f, 100.0f) * ForceAmount * BarrelMesh->GetMass());

	}
	else
	{
		BarrelMesh->AddForce(GetActorUpVector() * ForceAmount * BarrelMesh->GetMass());
	}
}

void ABarrelActor::TimeUp()
{
	UE_LOG(LogTemp,Warning,TEXT("BarrelTimer"))
	TimerEnd = true;
}