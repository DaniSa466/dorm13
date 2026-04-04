// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StrategyNPC.h"

class DORM13_API WanderState : public StrategyNPC
{
private:
	float axisX = 0.f;
	float moveSize = 200.f;

public:
	WanderState();
	virtual ~WanderState() override = default;
	virtual void Execute() override;
	virtual FString GetStateName() const override { return "wander"; }
	void DestinationReached();
};
