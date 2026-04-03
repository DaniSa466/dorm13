// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionEnvironment.h"
#include "Dorm13/player/PlayerCharacter.h"

AEnergyDrink::AEnergyDrink()
{
	itemName = FName("Energy Drink");
}

void AEnergyDrink::SetCharPointer(AActor* actorToUseItem)
{
	pointerToChar = Cast<APlayerCharacter>(actorToUseItem);
}

void AEnergyDrink::Execute()
{
	pointerToChar->IncreaseStamina(energyToRecovery);
}