// Fill out your copyright notice in the Description page of Project Settings.


#include "WannaEat.h"
#include "Dorm13/NPC/BaseNPCCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

WannaEat::WannaEat(AActor* target) : targetActor(target) {}

void WannaEat::Execute()
{
	if (!npc && !targetActor.IsValid())
		return;

	float direction = targetActor->GetActorLocation().X - npc->GetActorLocation().X;

	animToPlay = npc->GetAnimToPlay(GetStateName());
	npc->UnsetDestination();

	npc->GetCharacterMovement()->MaxWalkSpeed = 450.f;
	npc->SetRotation(direction > 0);
	npc->AddMovementInput(FVector(direction, 0.f, 0.f).GetSafeNormal(), 1.f);
	npc->PlayAnim(animToPlay);
}
