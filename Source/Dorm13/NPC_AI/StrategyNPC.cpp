// Fill out your copyright notice in the Description page of Project Settings.


#include "StrategyNPC.h"
#include "Dorm13/NPC/BaseNPCCharacter1.h"

StrategyNPC::StrategyNPC()
{
}

void StrategyNPC::InitState(APawn* pawnNPC)
{
	npc = Cast<ABaseNPCCharacter>(pawnNPC);
}

