// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	AIPawn = GetPawn();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//SetFocus(PlayerPawn);
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
	//RandomPatrol();

	for (AActor* Waypoint : Waypoints)
	{
		if (Waypoint->ActorHasTag(TEXT("Lookout")))
		{
			LookoutPoint = Waypoint;
		}
	}

	if(EnemyBehavior != nullptr)
	{
		RunBehaviorTree(EnemyBehavior);
	}
	/*GetBlackboardComponent()->SetValueAsVector(TEXT("LookoutPosition"), LookoutPoint->GetActorLocation());
	GetBlackboardComponent()->SetValueAsVector(TEXT("HomePosition"), AIPawn->GetActorLocation());*/

}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (CheckFront(PlayerPawn))
	{
		GetBlackboardComponent()->SetValueAsBool(TEXT("InFront"), true);
	}
	else
	{
		GetBlackboardComponent()->SetValueAsBool(TEXT("InFront"), false);

	}

}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	//GetWorld()->GetTimerManager().SetTimer(WaitTimer, this, &AEnemyAIController::TimeUp, WaitTime, false);

}

AActor* AEnemyAIController::ChooseWaypoint()
{
	int index = FMath::RandRange(0, Waypoints.Num() - 1);
	return Waypoints[index];
}

void AEnemyAIController::RandomPatrol()
{
	AActor* NextWaypoint = ChooseWaypoint();
	MoveToActor(NextWaypoint);

}

void AEnemyAIController::TimeUp()
{
	//RandomPatrol();
}

bool AEnemyAIController::CheckFront(AActor* ActorToCheck)
{
	
	FVector AIForwardVector = AIPawn->GetActorForwardVector(); //already nomalised
	FVector PlayerPositionVector = PlayerPawn->GetActorLocation();
	FVector AIPositionVector = AIPawn->GetActorLocation();
	FVector AIToPlayerVector = PlayerPositionVector - AIPositionVector;
	AIToPlayerVector.Normalize(); //this vector must be explicitly normalised
	float DirectionDotProduct = FVector::DotProduct(AIToPlayerVector, AIForwardVector);
	if (DirectionDotProduct > 0) return true;
	else return false;
}
