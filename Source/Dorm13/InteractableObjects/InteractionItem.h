// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AInteractableObject.h"
#include "PaperFlipbookActor.h"
#include "InteractableItem.h" 
#include "InteractionItem.generated.h"

class AlayerCharacter;
class UBoxComponent;

UCLASS(Blueprintable, BlueprintType)
class DORM13_API AEnergyDrink : public AAInteractableObject, public IInteractableItem
{
	GENERATED_BODY()

private:
	float energyToRecovery = 20.f;

public:
	AEnergyDrink();
	virtual void Execute() override;
	virtual void UseItem() override;
};

UCLASS(Blueprintable, BlueprintType)
class DORM13_API AFood : public AAInteractableObject, public IInteractableItem
{
	GENERATED_BODY()

private:
	AFood* spawnedFood;
	FTimerHandle TimerHandle_MoveTimer;

	void StartMoving();
	void Move();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	float minZ;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AFood> foodToSpawn;

public:
	AFood();
	virtual void Execute() override;
	virtual void UseItem() override;
};