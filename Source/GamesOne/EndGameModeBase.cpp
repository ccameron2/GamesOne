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
	GetWorld()->GetTimerManager().SetTimer(EndGameTimer, this, &AEndGameModeBase::TimeUp, GameDuration, false);
}

void AEndGameModeBase::TimeUp()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Level");
}
