// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/BoxComponent.h"
#include "AmmoActor.h"
#include "CoreMinimal.h"
#include "DestructibleActor.h"
#include "CustomDestructibleActor.generated.h"

/**
 * 
 */
UCLASS()
class GAMESONE_API ACustomDestructibleActor : public ADestructibleActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ACustomDestructibleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnFracture(const FVector& HitPoint, const FVector& HitDirection);
	UPROPERTY(EditAnywhere)
		TSubclassOf<AAmmoActor> AmmoClass;
};
