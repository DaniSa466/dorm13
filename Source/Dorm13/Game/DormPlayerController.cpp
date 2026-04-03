// Fill out your copyright notice in the Description page of Project Settings.


#include "DormPlayerController.h"

ADormPlayerController::ADormPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ADormPlayerController::PlayerTick(float deltaTime)
{
	Super::PlayerTick(deltaTime);
}

void ADormPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ADormPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

