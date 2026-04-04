// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StrategyNPC.h"

class DORM13_API IdleState : public StrategyNPC
{
public:
	IdleState();
	virtual ~IdleState() override = default;
	virtual void Execute() override;
	virtual FString GetStateName() const override { return "idle"; }
};
