// Fill out your copyright notice in the Description page of Project Settings.

#include "LandmineActor.h"

#include "PlayableCharacter.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ALandmineActor::ALandmineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//Create landmine mesh and set as root component
	LandmineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Landmine Mesh"));
	LandmineMesh->SetNotifyRigidBodyCollision(true);
	SetRootComponent(LandmineMesh);

	//Create radial force component and attach to landmine mesh
	ForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("Force Component"));
	ForceComp->SetupAttachment(LandmineMesh);

}

// Called when the game starts or when spawned
void ALandmineActor::BeginPlay()
{
	Super::BeginPlay();
	//Add dynamic delegate for hit event
	OnActorHit.AddDynamic(this, &ALandmineActor::OnHit);
	
}

void ALandmineActor::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHit"));
	if (OtherActor->GetClass()->IsChildOf(APlayableCharacter::StaticClass()))//If Other Actor is a Playable Character
	{
		AActor* ProjectileOwner = GetOwner();
		//Apply damage to actor
		UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, ProjectileOwner->GetInstigatorController(), this, UDamageType::StaticClass());
		//Spawn explosion actor
		AExplosion* Explosion;
		Explosion = GetWorld()->SpawnActor<AExplosion>(ExplosionClass, this->GetActorLocation(), this->GetActorRotation());
		//Play explosion sound at location
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
		//Fire radial force component
		ForceComp->FireImpulse();
		//Destroy actor
		Destroy();
	}
}

