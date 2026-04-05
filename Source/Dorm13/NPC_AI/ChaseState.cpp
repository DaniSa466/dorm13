// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaseState.h"
#include "Dorm13/NPC/BaseNPCCharacter.h"
#include "PaperFlipbook.h"
#include "GameFramework/CharacterMovementComponent.h"

ChaseState::ChaseState(AActor* target) : targetActor(target) {}

void ChaseState::Execute()
{
	if (!npc || !targetActor.IsValid())
		return;

	float direction = targetActor->GetActorLocation().X - npc->GetActorLocation().X;

	animToPlay = npc->GetAnimToPlay(GetStateName());
	npc->UnsetDestination();

	npc->GetCharacterMovement()->MaxWalkSpeed = 350.f;
	npc->AddMovementInput(FVector(direction, 0.f, 0.f).GetSafeNormal(), 1.f);
	npc->PlayAnim(animToPlay);
}

