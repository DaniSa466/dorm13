// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StrategyNPC.h"

class DORM13_API WannaEat : public StrategyNPC
{
private:
	TWeakObjectPtr<AActor> targetActor;

public:
	WannaEat(AActor* target);
	virtual ~WannaEat() override = default;
	virtual void Execute() override;
	virtual FString GetStateName() const override { return "wannaEat"; }
};
