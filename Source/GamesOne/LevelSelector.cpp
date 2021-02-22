// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSelector.h"
#include "Kismet/GameplayStatics.h"
#include "PlayableCharacter.h"

// Sets default values
ALevelSelector::ALevelSelector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create LevelSelector Mesh and set as root component
	SelectorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Selector Mesh"));
	SetRootComponent(SelectorMesh);

	//Create box component for overlap events and attach to root component
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetBoxExtent(FVector(60.0f, 60.0f, 30.0f));
	BoxComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALevelSelector::BeginPlay()
{
	Super::BeginPlay();
	//Create dynamic delegates for overlap events
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ALevelSelector::OnOverlapBegin);
	//Spawn spark actor slightly above selector mesh
	ASparks* Spark;
	Spark = GetWorld()->SpawnActor<ASparks>(SparkClass, this->GetActorLocation() + FVector(0.0f, 0.0f, 40.0f), this->GetActorRotation());
}


void ALevelSelector::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin"));
	if (Cast<APlayableCharacter>(OtherActor))//If other actor is a playable character
	{
		//Open designated level
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);
	}
}

