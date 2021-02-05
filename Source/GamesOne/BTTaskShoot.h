// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskShoot.generated.h"

/**
 * 
 */
UCLASS()
class GAMESONE_API UBTTaskShoot : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	APlayableCharacter* AIActor;
};
