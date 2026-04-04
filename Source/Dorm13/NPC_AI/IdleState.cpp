// Fill out your copyright notice in the Description page of Project Settings.


#include "IdleState.h"
#include "Dorm13/NPC/BaseNPCCharacter1.h"
#include "PaperFlipbook.h"
#include "GameFramework/CharacterMovementComponent.h"

IdleState::IdleState()
{
}

void IdleState::Execute()
{
	//npc->GetCharacterMovement()->MaxWalkSpeed = 0.f;
	animToPlay = npc->GetAnimToPlay(GetStateName());
	npc->PlayAnim(animToPlay);
}

