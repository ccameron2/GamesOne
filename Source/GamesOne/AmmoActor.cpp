// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomPlayerController.h"
#include "AmmoActor.h"

// Sets default values
AAmmoActor::AAmmoActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Selector Mesh"));
	AmmoMesh->SetupAttachment(RootComponent);
	AmmoMesh->SetSimulatePhysics(true);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetBoxExtent(FVector(10.0f, 10.0f, 10.0f));
	BoxComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAmmoActor::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AAmmoActor::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AAmmoActor::OnOverlapEnd);
}

// Called every frame
void AAmmoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmoActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	APlayableCharacter* OtherActorRef = Cast<APlayableCharacter>(OtherActor);
	ACustomPlayerController* Controller = Cast<ACustomPlayerController>(OtherActorRef->GetController());
	UE_LOG(LogTemp,Warning,TEXT("Reset Ammo"))
	Controller->ResetAmmoCount();
	Destroy();
}

void AAmmoActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

