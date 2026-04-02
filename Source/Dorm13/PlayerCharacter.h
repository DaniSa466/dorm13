// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class DORM13_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

private:
	float axisX = 0.f;
	bool sprint = false;
	float resSpeed = 300.f;

	float stamina = 100.f;
	float timeToDecreaseStamina = 0.1f;
	float timeToRecoveryStamina = 0.15f;
	FTimerHandle TimerHandle_StaminaDecrease;
	FTimerHandle TimerHandle_StaminaRecovery;

	void InputAxisX(float value);
	void MovementTick(float deltaSeconds);

	void DecreaseStamina();
	void RecoveryStamina();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SprintEnabled();
	void SprintDisabled();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	float GetStamina();

};
