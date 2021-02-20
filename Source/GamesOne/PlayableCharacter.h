// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GamesOneGameModeBase.h"
#include "DamagingActor.h"
#include "WeaponActor.h"
#include "LandmineActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CustomMovementComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayableCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USceneCaptureComponent2D;

UCLASS()
class GAMESONE_API APlayableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayableCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float MoveSpeed = 200.0f;

	UPROPERTY(EditAnywhere)
		float RotationSpeed = 500.0f;

	UPROPERTY(EditAnywhere)
		float HealthPoints = 100.0f;

	UFUNCTION(BlueprintPure)
		int GetHealth();

	UFUNCTION(BlueprintPure)
		int GetPoints();

	void MoveForward(float AxisValue);
	void Strafe(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);
	void Fire();
	void LandMine();
	void DamagingActor();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AWeaponActor> WeaponActorClass;

	UPROPERTY(EditAnywhere)
		AWeaponActor* WeaponActor;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ALandmineActor> LandmineActorClass;

	UPROPERTY(EditAnywhere)
		USceneComponent* LandmineSpawnPoint;

	UPROPERTY(EditAnywhere)
		USceneComponent* DamagingActorSpawnPoint;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ADamagingActor> DamagingActorClass;

	UPROPERTY(EditAnywhere)
		float BulletDamage = 20.0f;

	UPROPERTY(EditAnywhere)
		AGamesOneGameModeBase* GameModeRef;

	UPROPERTY(EditAnywhere)
		USceneComponent* RaycastingCastPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* CharacterMesh;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PawnMesh;

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
		UCustomMovementComponent* PawnMovement;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* MapArm;
	UPROPERTY(EditAnywhere)
		USceneCaptureComponent2D* MapCamera;

	UPROPERTY(EditAnywhere)
		USoundBase* HitSound;



};
