// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionEnvironment.generated.h"

class APlayerCharacter;

//abstract class
UCLASS(Abstract, Blueprintable)
class DORM13_API AAInteractionEnvironment : public AActor
{
	GENERATED_BODY()
	
protected:
	FName itemName;

public:	
	AAInteractionEnvironment()
	{
		itemName = NAME_None;
	}

	virtual ~AAInteractionEnvironment() = default;
	virtual void Execute() = 0;
	virtual FName GetItemName() { return itemName; }
};

UCLASS(Blueprintable, BlueprintType)
class DORM13_API AEnergyDrink : public AAInteractionEnvironment
{
private:
	float energyToRecovery = 20.f;
	class APlayerCharacter* pointerToChar = nullptr;

public:
	AEnergyDrink();
	void SetCharPointer(AActor* actorToUseItem);
	virtual void Execute() override;
};