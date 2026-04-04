// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"

class ABaseNPCCharacter;

class DORM13_API StrategyNPC
{
protected:
	class ABaseNPCCharacter* npc;
	UPaperFlipbook* animToPlay;
public:
	StrategyNPC();
	virtual ~StrategyNPC() = default;
	void InitState(APawn* pawnNPC);
	virtual void Execute() = 0;
	virtual FString GetStateName() const = 0;
};
