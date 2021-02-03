// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMESONE_API UCustomMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void MoveForward(float AxisValue);
	void Strafe(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);
	void Fire();
private:
	UPROPERTY(EditAnywhere)
		float MoveSpeed = 200.0f;
	UPROPERTY(EditAnywhere)
		float RotationSpeed = 500.0f;


};
