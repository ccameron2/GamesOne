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
	//Set score to 0
	score = 0;
	//Start game timer
	GetWorld()->GetTimerManager().SetTimer(EndGameTimer, this, &AGamesOneGameModeBase::TimeUp, GameDuration, false);
}

void AGamesOneGameModeBase::ScorePoint()
{
	UE_LOG(LogTemp, Warning, TEXT("PointScored!"));
	//Increment score
	score++;
	//Check if score is maximum
	if (score >= maximumScore)
	{
		//Load next level
		UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
	}
}

void AGamesOneGameModeBase::GameOver(bool gameWon)//Load winlevel or looselevel depending on paremeters
{
	if (gameWon) { UGameplayStatics::OpenLevel(GetWorld(), "WinLevel"); }
	else { UGameplayStatics::OpenLevel(GetWorld(), "LoseLevel"); }
}

void AGamesOneGameModeBase::TimeUp()
{
	//End game when timer reaches 0
	UE_LOG(LogTemp, Warning, TEXT("Time Up"));
	GameOver(false);
}

int AGamesOneGameModeBase::GetPoints()
{
	return score;
}

