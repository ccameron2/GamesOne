// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamagingActor.generated.h"

UCLASS()
class GAMESONE_API ADamagingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamagingActor();

protected:
	virtual void BeginPlay() override;

public:	


	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ActorMesh;

	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
		UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere)
		float MovementSpeed = 1000.0f;
	UPROPERTY(EditAnywhere)
		float DamageAmount = 20.0f;


};
