// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagingActor.h"
#include "PlayableCharacter.h"

// Sets default values
ADamagingActor::ADamagingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));

	SetRootComponent(ActorMesh);
	ActorMesh->SetSimulatePhysics(true);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->InitialSpeed = MovementSpeed;
	InitialLifeSpan = 8.0f;


}

void ADamagingActor::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &ADamagingActor::OnHit);

}

void ADamagingActor::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("On Hit"));
	if (OtherActor->GetClass()->IsChildOf(APlayableCharacter::StaticClass()))
	{
		AActor* ProjectileOwner = GetOwner();
		UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, ProjectileOwner->GetInstigatorController(), this, UDamageType::StaticClass());
		SelfActor->Destroy();
	}
}

