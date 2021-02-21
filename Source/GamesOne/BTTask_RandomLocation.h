// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "BehaviorTree/BlackboardComponent.h"

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class GAMESONE_API UBTTask_RandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;



public:
	UPROPERTY(EditAnywhere)
		float RandomRadius = 2000.0f;


};
