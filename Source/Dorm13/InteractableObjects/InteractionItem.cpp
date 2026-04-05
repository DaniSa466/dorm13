// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionItem.h"
#include "Components/BoxComponent.h"
#include "Dorm13/player/PlayerCharacter.h"



AEnergyDrink::AEnergyDrink()
{
	itemName = FName("Energy Drink");
}

void AEnergyDrink::Execute()
{
	if (pointerToChar)
		pointerToChar->TakeItemToInventory();
}

void AEnergyDrink::UseItem()
{
	if (pointerToChar)
		pointerToChar->IncreaseStamina(energyToRecovery);
}

void AFood::StartMoving()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_MoveTimer, this, &AFood::Move, 0.1f, true);
	}
}

void AFood::Move()
{
	FVector currentLocation = GetActorLocation();
	FVector newLocation = FVector(currentLocation.X + 5.f, 0.f, currentLocation.Z - 2.f);
	SetActorLocation(newLocation);

	if (newLocation.Z <= minZ)
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_MoveTimer);
}

AFood::AFood()
{
	itemName = FName("Food");
}

void AFood::Execute()
{
	if (pointerToChar)
		pointerToChar->TakeItemToInventory();
}

void AFood::UseItem()
{
	if (!pointerToChar)
		return;

	FVector spawnLocation = pointerToChar->GetActorLocation();
	spawnLocation.X += 50;

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	spawnParams.Owner = pointerToChar;
	spawnParams.Instigator = pointerToChar;

	if (GetWorld())
	{
		spawnedFood = Cast<AFood>(GetWorld()->SpawnActor(foodToSpawn, &spawnLocation, &FRotator::ZeroRotator, spawnParams));
		
		if (spawnedFood)
		{
			pointerToChar->AddFoodToWorld(spawnedFood);
			spawnedFood->SetPointerToChar(pointerToChar);
			spawnedFood->StartMoving();
			pointerToChar->ThroughtFood();
		}
	}

}

