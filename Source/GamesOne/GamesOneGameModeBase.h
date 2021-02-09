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
private:
	void StartGame();
	void GameOver(bool flip);

public:
	UFUNCTION()
		void PointScored();
	UPROPERTY()
		FTimerHandle EndGameTimer;
	UPROPERTY()
		float GameDuration = 100.0f;
	UFUNCTION()
		void TimeUp();
	UPROPERTY()
		int PointsScored = 0;

};
