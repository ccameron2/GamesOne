// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AEndGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	StartGame();
}

void AEndGameModeBase::StartGame()
{
	//Start timer to restart game if time runs out.
	GetWorld()->GetTimerManager().SetTimer(EndGameTimer, this, &AEndGameModeBase::TimeUp, GameDuration, false);
}

void AEndGameModeBase::TimeUp()
{
	UGameplayStatics::OpenLevel(GetWorld(), "StartLevel");
}
