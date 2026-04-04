// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StrategyNPC.h"

class DORM13_API ChaseState : public StrategyNPC
{
private:
	TWeakObjectPtr<AActor> targetActor;

public:
	ChaseState(AActor* target);
	virtual ~ChaseState() override = default;
	virtual void Execute() override;
	virtual FString GetStateName() const override { return "chase"; }
};
