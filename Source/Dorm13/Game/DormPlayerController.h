// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DormPlayerController.generated.h"

UCLASS()
class DORM13_API ADormPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ADormPlayerController();

protected:
	virtual void PlayerTick(float deltaTime) override;
	virtual void SetupInputComponent() override;

	virtual void OnUnPossess() override;
};
