// Copyright Epic Games, Inc. All Rights Reserved.


#include "GamesOneGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AGamesOneGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	StartGame();
}

void AGamesOneGameModeBase::StartGame()
{
	score = 0;
	GetWorld()->GetTimerManager().SetTimer(EndGameTimer, this, &AGamesOneGameModeBase::TimeUp, GameDuration, false);
}

void AGamesOneGameModeBase::ScorePoint()
{
	UE_LOG(LogTemp, Warning, TEXT("PointScored!"));
	score++;
	if (score >= maximumScore)
	{
		UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
	}
}

void AGamesOneGameModeBase::GameOver(bool gameWon)
{
	if (gameWon) { UGameplayStatics::OpenLevel(GetWorld(), "WinLevel"); }
	else { UGameplayStatics::OpenLevel(GetWorld(), "LoseLevel"); }


}

void AGamesOneGameModeBase::TimeUp()
{
	UE_LOG(LogTemp, Warning, TEXT("Time Up"));
	GameOver(false);
}

int AGamesOneGameModeBase::GetPoints()
{
	return score;
}
