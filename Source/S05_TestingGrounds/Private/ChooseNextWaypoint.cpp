// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"



EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("1 ExecuteTask called by %s"), *(OwnerComp.GetName()));

	return EBTNodeResult::Succeeded;
}
