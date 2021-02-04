// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskShoot.h"

EBTNodeResult::Type UBTTaskShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UE_LOG(LogTemp, Warning, TEXT("Shooting"));

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AIActor = Cast<APlayableCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	AIActor->Fire();

	return EBTNodeResult::Succeeded;

}