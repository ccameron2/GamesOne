// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomDestructibleActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACustomDestructibleActor::ACustomDestructibleActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create box component for overlap events and attach to root componenet.
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetBoxExtent(FVector(110.0f, 110.0f, 110.0f));
	BoxComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
	BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
	BoxComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACustomDestructibleActor::BeginPlay()
{
	Super::BeginPlay();

	//Add dynamic delegates for overlap events
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACustomDestructibleActor::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ACustomDestructibleActor::OnOverlapEnd);

	//Add dynamic delegate for fracture event
	OnActorFracture.AddDynamic(this, &ACustomDestructibleActor::OnFracture);
}

// Called every frame
void ACustomDestructibleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACustomDestructibleActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin"));
}

void ACustomDestructibleActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapEnd"));

}

void ACustomDestructibleActor::OnFracture(const FVector& HitPoint, const FVector& HitDirection)
{
	UE_LOG(LogTemp, Warning, TEXT("Shattered"));
}

