// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSelector.h"
#include "Kismet/GameplayStatics.h"
#include "PlayableCharacter.h"

// Sets default values
ALevelSelector::ALevelSelector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SelectorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Selector Mesh"));
	SelectorMesh->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetBoxExtent(FVector(60.0f, 60.0f, 30.0f));
	BoxComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
	BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
	BoxComponent->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ALevelSelector::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ALevelSelector::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ALevelSelector::OnOverlapEnd);
}

// Called every frame
void ALevelSelector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSelector::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin"));
	if (Cast<APlayableCharacter>(OtherActor))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);
	}
}

void ALevelSelector::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapEnd"));
}

