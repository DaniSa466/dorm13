// Fill out your copyright notice in the Description page of Project Settings.


#include "StrategyNPC.h"
#include "Dorm13/NPC/BaseNPCCharacter.h"

StrategyNPC::StrategyNPC()
{
}

void StrategyNPC::InitState(APawn* pawnNPC)
{
	npc = Cast<ABaseNPCCharacter>(pawnNPC);
}

