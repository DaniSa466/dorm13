// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class IInteractableItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DORM13_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	int8 maxInventoryCount = 3;
	TArray<class IInteractableItem*> inventoryArray;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddItemToInventory(IInteractableItem* itemToAdd);
	void RemoveItemFromInventory(IInteractableItem* itemToRemove);
	IInteractableItem* GetItemByIndex(int32 itemIndex);
	
	UFUNCTION(BlueprintCallable)
	int32 GetInventoryLenght();
	UFUNCTION(BlueprintCallable)
	int32 GetMaxInventoryLenght();
};
