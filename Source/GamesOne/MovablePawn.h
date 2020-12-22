// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// Add camera and spring arm.
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CustomMovementComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MovablePawn.generated.h"

UCLASS()
class GAMESONE_API AMovablePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMovablePawn();
	UPROPERTY(EditAnywhere)
		UCustomMovementComponent* PawnMovement;

protected:

private:	
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PawnMesh;

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;
};
