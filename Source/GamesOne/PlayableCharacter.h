// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "WeaponActor.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CustomMovementComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayableCharacter.generated.h"

UCLASS()
class GAMESONE_API APlayableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayableCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		float MoveSpeed = 200.0f;
	UPROPERTY(EditAnywhere)
		float RotationSpeed = 500.0f;

	void MoveForward(float AxisValue);
	void Strafe(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);
	void Fire();

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
		TSubclassOf<AWeaponActor> WeaponActorClass;

	UPROPERTY(EditAnywhere)
		AWeaponActor* WeaponActor;
};
