// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StrategyNPC.h"


class DORM13_API AttackState : public StrategyNPC
{
private:
	TWeakObjectPtr<AActor> target;

public:
	AttackState(AActor* targetActor);
	virtual ~AttackState() override = default;
	virtual void Execute() override;
	virtual FString GetStateName()const override { return "attack"; }
};
