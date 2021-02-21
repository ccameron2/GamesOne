// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerPosition.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_PlayerPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//Pass player location to blackboard component
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),PlayerPawn->GetActorLocation());
}
