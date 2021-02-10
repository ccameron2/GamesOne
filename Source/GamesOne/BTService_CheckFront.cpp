// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckFront.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_CheckFront::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* EnemyAIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = EnemyAIController->GetPawn();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	FVector AIForwardVector = AIPawn->GetActorForwardVector(); //already nomalised
	FVector PlayerPositionVector = AIPawn->GetActorLocation();
	FVector AIPositionVector = AIPawn->GetActorLocation();
	FVector AIToPlayerVector = PlayerPositionVector - AIPositionVector;
	AIToPlayerVector.Normalize(); //this vector must be explicitly normalised
	float DirectionDotProduct = FVector::DotProduct(AIToPlayerVector, AIForwardVector);
	
	if (DirectionDotProduct > 0)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}