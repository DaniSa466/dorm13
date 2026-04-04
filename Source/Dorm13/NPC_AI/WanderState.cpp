// Fill out your copyright notice in the Description page of Project Settings.


#include "WanderState.h"
#include "Dorm13/NPC/BaseNPCCharacter1.h"
#include "Dorm13/NPC/NPCController.h"
#include "GameFramework/CharacterMovementComponent.h"

WanderState::WanderState()
{
}

void WanderState::Execute()
{
	if (FMath::FRand() < 0.5f)
		axisX = -1.f;
	else
		axisX = 1.f;

	npc->GetCharacterMovement()->MaxWalkSpeed = 300.f;
	animToPlay = npc->GetAnimToPlay(GetStateName());
	npc->OnDestinationReached.BindRaw(this, &WanderState::DestinationReached);

	if (npc->CheckCanMove(moveSize * axisX))
		npc->MoveActor(moveSize * axisX);
	else
		npc->MoveActor(moveSize * (-axisX));

	npc->SetRotation(axisX);
	npc->PlayAnim(animToPlay);
}

void WanderState::DestinationReached()
{
	npc->OnDestinationReached.Unbind();
	npc->GetController<ANPCController>()->ChooseCalmState();
}

