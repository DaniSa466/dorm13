// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Dorm13//player/PlayerCharacter.h"
#include "Dorm13/InteractableObjects/InteractableItem.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::AddItemToInventory(IInteractableItem* itemToAdd)
{
	inventoryArray.Add(itemToAdd);
 }

void UInventoryComponent::RemoveItemFromInventory(IInteractableItem* itemToRemove)
{
	inventoryArray.Remove(itemToRemove);
}

IInteractableItem* UInventoryComponent::GetItemByIndex(int32 itemIndex)
{
	if (inventoryArray.IsValidIndex(itemIndex) && inventoryArray[itemIndex])
		return inventoryArray[itemIndex];

	return nullptr;
}

int32 UInventoryComponent::GetInventoryLenght()
{
	return inventoryArray.Num();
}

int32 UInventoryComponent::GetMaxInventoryLenght()
{
	return maxInventoryCount;
}

