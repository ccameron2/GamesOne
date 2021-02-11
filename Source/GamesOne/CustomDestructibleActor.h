// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/BoxComponent.h"
#include "GamesOneGameModeBase.h"

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
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxComponent;

	UPROPERTY()
		AGamesOneGameModeBase* GameModeRef;

	UFUNCTION()
		void OnFracture(const FVector& HitPoint, const FVector& HitDirection);

};
