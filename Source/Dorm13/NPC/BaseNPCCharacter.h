// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "NPCController.h"
#include "BaseNPCCharacter.generated.h"

DECLARE_DELEGATE(FOnDestinationReached);

UCLASS()
class DORM13_API ABaseNPCCharacter : public APaperCharacter
{
	GENERATED_BODY()

private:
	UPaperFlipbookComponent* flipBookComponent = nullptr;
	ANPCController* npcController;

	float resSpeed = 400.f;
	FVector baseLocation;
	float maxDeviation = 300.f;
	FVector destination = FVector(0.f, 300.f, 0.f);
	FVector direction;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* idleAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* chaseAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* wanderAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* hitAnimation;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	ABaseNPCCharacter();

	void PlayAnim(UPaperFlipbook* anim);
	void PlayAnimOnce(UPaperFlipbook* anim);
	UPaperFlipbook* GetAnimToPlay(FString stateName);
	void MoveActor(float move);
	bool CheckCanMove(float moveSide);
	void UnsetDestination();


	FOnDestinationReached OnDestinationReached;
};
