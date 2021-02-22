// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BulletActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class GAMESONE_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION()
		void OnFire();

	UPROPERTY(EditAnywhere, Category = "SpawnClass")
		TSubclassOf<ABulletActor> BulletClass;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* GunMesh;

private:


	UPROPERTY(EditAnywhere)
		USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* GunSkeletalMesh;
	
	UPROPERTY(EditAnywhere)
		USoundBase* GunshotSound;

};
