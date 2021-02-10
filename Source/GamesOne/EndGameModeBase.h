// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMESONE_API AEndGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	void StartGame();
	void TimeUp();

public:
	UPROPERTY()
		FTimerHandle EndGameTimer;
	UPROPERTY()
		float GameDuration = 10.0f;
};
