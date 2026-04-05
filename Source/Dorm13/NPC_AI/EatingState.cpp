// Fill out your copyright notice in the Description page of Project Settings.


#include "EatingState.h"
#include "Dorm13/NPC/BaseNPCCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

EatingState::EatingState(AActor* targetActor) : target(targetActor) {}

void EatingState::Execute()
{
	npc->GetCharacterMovement()->MaxWalkSpeed = 0.f;

	animToPlay = npc->GetAnimToPlay(GetStateName());
	npc->PlayAnim(animToPlay);
}
