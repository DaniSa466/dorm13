// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "PaperSpriteComponent.h"
#include "AInteractableObject.generated.h"

class AlayerCharacter;
class UBoxComponent;
class APlayerCharacter;


UCLASS(Abstract, Blueprintable)
class DORM13_API AAInteractableObject : public APaperFlipbookActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	FName itemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* boxCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprite")
	UPaperSpriteComponent* sprite;
	UPROPERTY()
	class APlayerCharacter* pointerToChar = nullptr;

public:
	AAInteractableObject();

	virtual ~AAInteractableObject() = default;
	virtual void Execute() {};
	virtual FName GetItemName() { return itemName; }
	virtual void SetPointerToChar(APlayerCharacter* pointer) { pointerToChar = pointer; }
};

