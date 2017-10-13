// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrollingGuard.h" //TODo remove coupling
#include "AIController.h"



EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//UE_LOG(LogTemp, Warning, TEXT("1 ExecuteTask called by %s"), *(OwnerComp.GetName()));

	UBlackboardComponent *BlackboardComp = OwnerComp.GetBlackboardComponent();
	int Index = BlackboardComp->GetValueAsInt(this->m_IndexKey.SelectedKeyName);

	//TODO protect against empty patrol routes

	TArray<AActor*> PatrolPoints = this->GetPatrolPoints(OwnerComp);
	this->SetNextWaypoint(BlackboardComp, Index, PatrolPoints);
	this->CycleIndex(BlackboardComp, Index, PatrolPoints);

	UE_LOG(LogTemp, Warning, TEXT("Patrol point size : %i"), PatrolPoints.Num());

	return EBTNodeResult::Succeeded;
}

TArray<AActor*> UChooseNextWaypoint::GetPatrolPoints(UBehaviorTreeComponent& OwnerComp)
{
	AAIController *AIController = OwnerComp.GetAIOwner();
	APawn *AIPawn = AIController->GetPawn();

	return Cast<APatrollingGuard>(AIPawn)->m_PatrolPoints;
}

void UChooseNextWaypoint::SetNextWaypoint(UBlackboardComponent *BlackboardComp, int IndexCurrent, TArray<AActor*> &PatrolPoints)
{
	BlackboardComp->SetValueAsObject(this->m_WaypointKey.SelectedKeyName, PatrolPoints[IndexCurrent]);
}

void UChooseNextWaypoint::CycleIndex(UBlackboardComponent *BlackboardComp, int IndexCurrent, TArray<AActor*> &PatrolPoints)
{
	//Increment index to indicate ai to go to next patrol point
	int NextIndex = (IndexCurrent + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(this->m_IndexKey.SelectedKeyName, NextIndex);
}
