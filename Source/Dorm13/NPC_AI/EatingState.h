// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StrategyNPC.h"

class DORM13_API EatingState : public StrategyNPC
{
private:
	TWeakObjectPtr<AActor> target;

public:
	EatingState(AActor* targetActor);
	virtual ~EatingState() override = default;
	virtual void Execute() override;
	virtual FString GetStateName() const override { return "eating"; }

	void EatFood();
};
