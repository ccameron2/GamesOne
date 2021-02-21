// Fill out your copyright notice in the Description page of Project Settings.

#include "AmmoActor.h"
#include "CustomPlayerController.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AAmmoActor::AAmmoActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Create Ammo Mesh and set as root component
	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ammo Mesh"));
	SetRootComponent(AmmoMesh);
	AmmoMesh->SetSimulatePhysics(true);

	//Create Box Component for overlap events
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
	//Add dynamic delegates
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AAmmoActor::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AAmmoActor::OnOverlapEnd);
}

// Called every frame
void AAmmoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Make ammo spin slowly
	AmmoMesh->AddTorqueInDegrees(FVector(0.0f, 0.0f, RotationSpeed));

}

void AAmmoActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APlayableCharacter>(OtherActor))//If overlapped by a playable character
	{
		APlayableCharacter* OtherActorRef = Cast<APlayableCharacter>(OtherActor);
		if (Cast<ACustomPlayerController>(OtherActorRef->GetController()))//If the controller of that character is Custom Player Controller
		{
			//Reset ammo count for player
			ACustomPlayerController* Controller = Cast<ACustomPlayerController>(OtherActorRef->GetController());
			UE_LOG(LogTemp, Warning, TEXT("Reset Ammo"));
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
			Controller->ResetAmmoCount();
		}
		Destroy();
	}
}
	

void AAmmoActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

