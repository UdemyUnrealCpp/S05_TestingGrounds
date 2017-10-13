// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class S05_TESTINGGROUNDS_API UChooseNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;	




protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector m_IndexKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector m_WaypointKey;

private:

	bool GetPatrolPoints(UBehaviorTreeComponent& OwnerComp, TArray<AActor*> *PatrolPoints);

	void SetNextWaypoint(UBlackboardComponent *BlackboardComp, const int IndexCurrent, const TArray<AActor*> &PatrolPoints);

	void CycleIndex(UBlackboardComponent *BlackboardComp, const int IndexCurrent, const TArray<AActor*> &PatrolPoints);
};
