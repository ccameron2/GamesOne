// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagingActor.h"
#include "PlayableCharacter.h"

// Sets default values
ADamagingActor::ADamagingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));
	ActorMesh->SetupAttachment(RootComponent);
	SetRootComponent(ActorMesh);
	InitialLifeSpan = 5;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("Force Component"));
	ForceComp->SetupAttachment(ActorMesh);

	ActorMesh->SetSimulatePhysics(true);
}

void ADamagingActor::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &ADamagingActor::OnHitFlag);
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
	if (OtherActor->GetClass()->IsChildOf(APlayableCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Playablecharacter"));
		AActor* ProjectileOwner = GetOwner();
		UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, ProjectileOwner->GetInstigatorController(), this, UDamageType::StaticClass());
		Explode();
	}
}
void ADamagingActor::Explode()
{
	UE_LOG(LogTemp, Warning, TEXT("Explode"));
	if (ForceComp != nullptr)
	{
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