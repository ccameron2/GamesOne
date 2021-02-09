// Copyright Epic Games, Inc. All Rights Reserved.


#include "GamesOneGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AGamesOneGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	StartGame();
}
void AGamesOneGameModeBase::PointScored()
{
	UE_LOG(LogTemp, Warning, TEXT("PointScored!"));
	//PointsScored++;
	/*if (PointsScored <= 5)
	{
	}
	else
	{
		GameOver(true);
	}*/
}

void AGamesOneGameModeBase::StartGame()
{
	GetWorld()->GetTimerManager().SetTimer(EndGameTimer, this, &AGamesOneGameModeBase::TimeUp, GameDuration, false);
}

void AGamesOneGameModeBase::GameOver(bool flip)
{
	if (flip) { UGameplayStatics::OpenLevel(GetWorld(), "EndLevel"); }
	else { UGameplayStatics::OpenLevel(GetWorld(), "LoseLevel"); }
}

void AGamesOneGameModeBase::TimeUp()
{
	UE_LOG(LogTemp, Warning, TEXT("Time Up"));
	GameOver(false);
}