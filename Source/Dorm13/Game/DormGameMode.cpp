// Fill out your copyright notice in the Description page of Project Settings.


#include "DormGameMode.h"
#include "DormPlayerController.h"
#include "Dorm13/player/PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"

ADormGameMode::ADormGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ADormPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/blueprints/BP_PlayerChar"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	else
	{
		DefaultPawnClass = APlayerCharacter::StaticClass();
	}
}
