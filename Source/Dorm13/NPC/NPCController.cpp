// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCController.h"
#include "Dorm13/NPC_AI/IdleState.h"
#include "Dorm13/NPC_AI/ChaseState.h"
#include "Dorm13/NPC_AI/WanderState.h"
#include "BaseNPCCharacter1.h"
#include "Kismet/GameplayStatics.h"

ANPCController::ANPCController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANPCController::BeginPlay()
{
	Super::BeginPlay();
	

	SetStrategy(MakeUnique<IdleState>());	
	ChooseCalmState();
	player = UGameplayStatics::GetPlayerPawn(this, 0);

	distanceToPlayer = FMath::Abs(GetPawn()->GetActorLocation().X - player->GetActorLocation().X);
}

void ANPCController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (currentStrategy)
		currentStrategy->Execute();

	float newDistance = FMath::Abs(GetPawn()->GetActorLocation().X - player->GetActorLocation().X);
	bool signChange;
	if (isChasing)
		signChange = distanceToPlayer < distToChace * 1.8f && distToChace * 1.8f < newDistance;
	else
		signChange = distanceToPlayer > distToChace && distToChace > newDistance;

	distanceToPlayer = newDistance;
	UE_LOG(LogTemp, Warning, TEXT("distance between player and NPC is %f"), distanceToPlayer);
	UE_LOG(LogTemp, Warning, TEXT("distance between player and NPC is %s"), *currentStrategy->GetStateName());

	if (signChange)
	{
		DecideWhichStrategyToUse();
	}

}

void ANPCController::SetStrategy(TUniquePtr<StrategyNPC> newStrategy)
{
	if (newStrategy.IsValid())
	{
		currentStrategy = MoveTemp(newStrategy);
		currentStrategy->InitState(GetPawn());

		if (GetWorld())
			if (currentStrategy->GetStateName() == "idle")
				GetWorld()->GetTimerManager().SetTimer(TimerHandle_CalmStateTimer, this, &ANPCController::ChooseCalmState, 0.5f, true);
			else
				GetWorld()->GetTimerManager().ClearTimer(TimerHandle_CalmStateTimer);
		else
			UE_LOG(LogTemp, Error, TEXT("ANPCCOntroller::SetStrategy - no world, can't use timer handle"));
	}
}

void ANPCController::DecideWhichStrategyToUse()
{
	if (!GetPawn() || !player)
		return;

	if (distanceToPlayer < distToChace)
	{
		if (currentStrategy->GetStateName() != "chase")
		{
			SetStrategy(MakeUnique<ChaseState>(player));
			tickStrategy = true;
			isChasing = true;
		}
	}
	else
	{
		tickStrategy = false;
		ChooseCalmState();
	}
}

void ANPCController::ChooseCalmState()
{
	if (FMath::FRand() < 0.2f)
	{
		if (currentStrategy->GetStateName() != "idle")
			SetStrategy(MakeUnique<IdleState>());
	}
	else
		SetStrategy(MakeUnique<WanderState>());

	isChasing = false;
	currentStrategy->Execute();
}


