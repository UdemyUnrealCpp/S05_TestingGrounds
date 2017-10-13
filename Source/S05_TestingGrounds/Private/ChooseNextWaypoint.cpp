// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"



EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//UE_LOG(LogTemp, Warning, TEXT("1 ExecuteTask called by %s"), *(OwnerComp.GetName()));

	UBlackboardComponent *BlackboardComp = OwnerComp.GetBlackboardComponent();
	int Index = BlackboardComp->GetValueAsInt(this->m_IndexKey.SelectedKeyName);

	//TODO protect against empty patrol routes

	TArray<AActor*> PatrolPoints;
	if (this->GetPatrolPoints(OwnerComp, &PatrolPoints)) //protect against no patrol route component & against empty patrol routes
	{	
		this->SetNextWaypoint(BlackboardComp, Index, PatrolPoints);
		this->CycleIndex(BlackboardComp, Index, PatrolPoints);

		UE_LOG(LogTemp, Warning, TEXT("Patrol point size : %i"), PatrolPoints.Num());
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

bool UChooseNextWaypoint::GetPatrolPoints(UBehaviorTreeComponent& OwnerComp, TArray<AActor*> *PatrolPoints)
{
	AAIController *AIController = OwnerComp.GetAIOwner();
	APawn *AIPawn = AIController->GetPawn();
	UPatrolRoute *PatrolRouteComp = Cast<UPatrolRoute>(AIPawn->FindComponentByClass<UPatrolRoute>());	
	
	//protect against no patrol route component	
	if (!ensure(PatrolRouteComp)) { return false; }

	///UE_LOG(LogTemp, Warning, TEXT("1_ : %i"), (*PatrolPoints).Num());
	*PatrolPoints = PatrolRouteComp->GetPatrolPoints();
	///UE_LOG(LogTemp, Warning, TEXT("2_ : %i"), PatrolPoints->Num());

	if ((*PatrolPoints).Num() == 0) //protect against empty patrol routes
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard is missing patrol points"));
		return false;
	}

	return true;
}

void UChooseNextWaypoint::SetNextWaypoint(UBlackboardComponent *BlackboardComp, const int IndexCurrent, const TArray<AActor*> &PatrolPoints)
{
	BlackboardComp->SetValueAsObject(this->m_WaypointKey.SelectedKeyName, PatrolPoints[IndexCurrent]);
}

void UChooseNextWaypoint::CycleIndex(UBlackboardComponent *BlackboardComp, const int IndexCurrent, const TArray<AActor*> &PatrolPoints)
{
	//Increment index to indicate ai to go to next patrol point
	int NextIndex = (IndexCurrent + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(this->m_IndexKey.SelectedKeyName, NextIndex);
}
