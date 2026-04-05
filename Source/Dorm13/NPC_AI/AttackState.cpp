// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackState.h"
#include "Dorm13/NPC/BaseNPCCharacter.h"
#include "Dorm13/player/PlayerCharacter.h"

AttackState::AttackState(AActor* targetActor) : target(targetActor) {}

void AttackState::Execute()
{
	APlayerCharacter* player = Cast<APlayerCharacter>(target);
	if (player)
	{
		if (player->healthComponent)
			player->DecreaseHealth();
	}

	animToPlay = npc->GetAnimToPlay(GetStateName());
	npc->PlayAnimOnce(animToPlay);
}

