// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BlackboardComponent.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAMESONE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	APawn* PlayerPawn;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


private:

	UPROPERTY(EditAnywhere)
		UBehaviorTree* EnemyBehavior;

	bool CheckFront(AActor* ActorToCheck);

	APawn* AIPawn;
};
