// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	AIPawn = GetPawn();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//Load Behaviour tree
	if(EnemyBehavior != nullptr)
	{
		RunBehaviorTree(EnemyBehavior);
	}

}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Output the results of dot product check to Blackboard.
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
}


bool AEnemyAIController::CheckFront(AActor* ActorToCheck)
{
	
	FVector AIForwardVector = AIPawn->GetActorForwardVector(); 
	FVector PlayerPositionVector = PlayerPawn->GetActorLocation();
	FVector AIPositionVector = AIPawn->GetActorLocation();
	FVector AIToPlayerVector = PlayerPositionVector - AIPositionVector;
	AIToPlayerVector.Normalize(); 
	//Calculate dot product to check if the actor can see the player or not.
	float DirectionDotProduct = FVector::DotProduct(AIToPlayerVector, AIForwardVector);
	if (DirectionDotProduct > 0) return true;
	else return false;
}
