// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootableActor.generated.h"

class URadialForceComponent;

UCLASS()
class GAMESONE_API AShootableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShootableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ActorMesh;

	UPROPERTY(EditAnywhere)
		float ForceAmount = 950.0f;
	UPROPERTY(EditAnywhere)
		float TorqueAmount = 10.0f;
};
