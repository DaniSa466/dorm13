// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCController.h"
#include "Dorm13/NPC_AI/IdleState.h"
#include "Dorm13/NPC_AI/ChaseState.h"
#include "Dorm13/NPC_AI/WanderState.h"
#include "Dorm13/NPC_AI/AttackState.h"
#include "BaseNPCCharacter.h"
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

	if (tickStrategy)
		currentStrategy->Execute();

	float newDistance = FMath::Abs(GetPawn()->GetActorLocation().X - player->GetActorLocation().X);
	bool signChange;
	if (isChasing)
		signChange = distanceToPlayer < distToChace * 1.8f && distToChace * 1.8f < newDistance;
	else
		signChange = distanceToPlayer > distToChace && distToChace > newDistance;

	if (!signChange)
		if (isAttacking)
			signChange = distanceToPlayer < distanceToAttack && distanceToAttack < newDistance;
		else
			signChange = distanceToPlayer > distanceToAttack && distanceToAttack > newDistance;

	distanceToPlayer = newDistance;

	if (signChange)
	{
		DecideWhichStrategyToUse();
	}

	UE_LOG(LogTemp, Warning, TEXT("Current strategy is %f"), distanceToPlayer);
	UE_LOG(LogTemp, Warning, TEXT("Current strategy is %s"), *currentStrategy->GetStateName());
}

void ANPCController::SetStrategy(TUniquePtr<StrategyNPC> newStrategy)
{
	if (newStrategy.IsValid())
	{
		currentStrategy = MoveTemp(newStrategy);
		currentStrategy->InitState(GetPawn());

		if (GetWorld())
		{
			{
				//idle timer
				if (currentStrategy->GetStateName() == "idle")
					GetWorld()->GetTimerManager().SetTimer(TimerHandle_CalmStateTimer, this, &ANPCController::ChooseCalmState, 0.5f, true);
				else
					GetWorld()->GetTimerManager().ClearTimer(TimerHandle_CalmStateTimer);
			}

			{
				//attack timer
				if (currentStrategy->GetStateName() == "attack")
				{
					Attack();
					GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackTimer, this, &ANPCController::Attack, 2.f, true);
				}
				else
				{
					GetWorld()->GetTimerManager().ClearTimer(TimerHandle_AttackTimer);
				}
			}
		}
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
		isChasing = true;
		if (distanceToPlayer < distanceToAttack)
		{
			if (currentStrategy->GetStateName() != "attack")
			{
				SetStrategy(MakeUnique<AttackState>(player));
				tickStrategy = false;
				isAttacking = true;
			}
		}
		else
		{
			if (currentStrategy->GetStateName() != "chase")
			{
				SetStrategy(MakeUnique<ChaseState>(player));
				tickStrategy = true;
				isAttacking = false;
			}
		}
	}
	else
	{
		tickStrategy = false;
		ChooseCalmState();
	}
}

void ANPCController::Attack()
{
	if (currentStrategy->GetStateName() == "attack")
		currentStrategy->Execute();
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

void ANPCController::Wait(float seconds)
{
	if (GetWorld())
	{
		SetStrategy(MakeUnique<IdleState>());
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_WaitTimer, this, &ANPCController::OnWaitFinished, false);
	}
}

void ANPCController::OnWaitFinished()
{
	ChooseCalmState();
}


