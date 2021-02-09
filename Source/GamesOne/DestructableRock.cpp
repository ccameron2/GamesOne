// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructableRock.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADestructableRock::ADestructableRock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock Mesh"));
	SetRootComponent(RockMesh);
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetBoxExtent(FVector(110.0f, 110.0f, 110.0f));
	BoxComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
	BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
	BoxComponent->SetupAttachment(RockMesh);

	GameModeRef = Cast<AGamesOneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

}

// Called when the game starts or when spawned
void ADestructableRock::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADestructableRock::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ADestructableRock::OnOverlapEnd);
	
}

// Called every frame
void ADestructableRock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructableRock::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin"));
	GameModeRef->PointScored();
}

void ADestructableRock::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapEnd"));

}

