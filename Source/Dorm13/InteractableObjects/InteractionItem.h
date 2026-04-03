// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "InteractionItem.generated.h"

class AlayerCharacter;
class UBoxComponent;

UCLASS(Abstract, Blueprintable)
class DORM13_API AAInteractionItem : public APaperFlipbookActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	FName itemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* boxCollision;

public:
	AAInteractionItem();

	virtual ~AAInteractionItem() = default;
	virtual void Execute() {};
	virtual FName GetItemName() { return itemName; }
};

UCLASS(Blueprintable, BlueprintType)
class DORM13_API AEnergyDrink : public AAInteractionItem
{
	GENERATED_BODY()

private:
	float energyToRecovery = 20.f;
	UPROPERTY()
	class APlayerCharacter* pointerToChar = nullptr;

public:
	AEnergyDrink();
	void SetCharPointer(AActor* actorToUseItem);
	virtual void Execute() override;
};
