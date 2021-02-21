// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagingActor.h"
#include "PlayableCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADamagingActor::ADamagingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Create Grenade mesh and set as root component
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));
	SetRootComponent(ActorMesh);

	InitialLifeSpan = 5;

	//Create projectile movement componenet and set speeds.
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->InitialSpeed = MovementSpeed;

	//Create Radial force component and attach to mesh
	ForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("Force Component"));
	ForceComp->SetupAttachment(ActorMesh);

	ActorMesh->SetSimulatePhysics(true);
}

void ADamagingActor::BeginPlay()
{
	Super::BeginPlay();
	//Add dynamic delegate for hit flag event
	OnActorHit.AddDynamic(this, &ADamagingActor::OnHitFlag);

	//Start fuse timer 
	GetWorld()->GetTimerManager().SetTimer(ExplodeTimer, this, &ADamagingActor::TimeUp, FuseTime, false);
}

void ADamagingActor::OnHitFlag(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("On Hit"));
	if (OtherActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("OtherActor Nullptr"));
		return;
	}
	if (OtherActor->GetClass()->IsChildOf(APlayableCharacter::StaticClass())) //If other actor is a Playable Character,
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Playablecharacter"));
		AActor* ProjectileOwner = GetOwner();
		//Apply damage to the other actor 
		UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, ProjectileOwner->GetInstigatorController(), this, UDamageType::StaticClass());
		Explode();
	}
}
void ADamagingActor::Explode()
{
	//Spawn explosion actor
	AExplosion* Explosion;
	Explosion = GetWorld()->SpawnActor<AExplosion>(ExplosionClass, this->GetActorLocation(), this->GetActorRotation());

	//Play explosion sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("Explode"));

	if (ForceComp != nullptr)
	{
		//Fire radial impulse componenet
		UE_LOG(LogTemp, Warning, TEXT("FireImpulse"));
		ForceComp->FireImpulse();
		Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ForceComp is Null"));
	}
}

void ADamagingActor::TimeUp()
{
	Explode();
}