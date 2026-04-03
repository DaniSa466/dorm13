// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AAInteractionItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DORM13_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	int8 maxInventoryCount = 3;
	TArray<class AAInteractionItem*> inventoryArray;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddItemToInventory(AAInteractionItem* itemToAdd);
	AAInteractionItem* GetItemByIndex(int32 itemIndex);
	
	UFUNCTION(BlueprintCallable)
	int32 GetInventoryLenght();
	UFUNCTION(BlueprintCallable)
	int32 GetMaxInventoryLenght();
};
