// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

UCLASS()
class GAMESONE_API ABulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActor();

protected:


public:	


	UPROPERTY(EditAnywhere)
		float MovementSpeed = 300.0f;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditAnywhere)
		UProjectileMovementComponent* ProjectileMovement;


};
