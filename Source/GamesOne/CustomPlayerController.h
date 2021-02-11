// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayableCharacter.h"
#include "MovablePawn.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMESONE_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	virtual void SetupInputComponent();
	APlayableCharacter* MyPawn;

private:
	virtual void CallForward(float AxisValue);
	virtual void CallTurn(float AxisValue);
	virtual void CallFire();
	virtual void CallStrafe(float Value);
	virtual void CallJump();
	virtual void CallLookUp(float Value);
	virtual void CallLandMine();
	virtual void CallDamagingActor();

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere)
		int NumberOfShots;

	UPROPERTY()
		UUserWidget* HUDWidget;

	UFUNCTION(BlueprintPure)
		int GetShots();

	UFUNCTION(BlueprintPure)
		int GetHealth();

	UPROPERTY(EditAnywhere)
		int PlayerHealth;

	UFUNCTION(BlueprintPure)
		int GetPoints();


};
