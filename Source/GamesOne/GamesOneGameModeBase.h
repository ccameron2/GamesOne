// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GamesOneGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMESONE_API AGamesOneGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION()
		void GameOver(bool gameWon);
	UFUNCTION()
		void ScorePoint();

private:
	UFUNCTION()
		void StartGame();
	UPROPERTY()
		FTimerHandle EndGameTimer;
	UPROPERTY()
		float GameDuration = 180.0f;
	UFUNCTION()
		void TimeUp();
	UPROPERTY()
		int score;

};
