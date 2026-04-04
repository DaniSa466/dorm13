// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dorm13/NPC_AI/StrategyNPC.h"
#include "AIController.h"
#include "NPCController.generated.h"

/**
 * 
 */
UCLASS()
class DORM13_API ANPCController : public AAIController
{
	GENERATED_BODY()
	
public:
	ANPCController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

private:
	bool tickStrategy = false;
	bool isChasing = false;
	float distanceToPlayer;
	float distToChace = 100.f;
	TUniquePtr<StrategyNPC> currentStrategy;
	AActor* player = nullptr;

	FTimerHandle TimerHandle_CalmStateTimer;

	void SetStrategy(TUniquePtr<StrategyNPC> newStrategy);
	void DecideWhichStrategyToUse();

public:
	void ChooseCalmState();
};
