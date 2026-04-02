// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	if (healthComponent)
		healthComponent->OnDead.AddDynamic(this, &APlayerCharacter::Death);

	GetCharacterMovement()->MaxWalkSpeed = resSpeed;
}

void APlayerCharacter::InputAxisX(float value)
{
	axisX = value;
}

void APlayerCharacter::MovementTick(float deltaTime)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), axisX);
}


void APlayerCharacter::DecreaseStamina()
{
	if (stamina > 0)
		if (axisX != 0)
			stamina--;
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_StaminaDecrease);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_StaminaRecovery, this, &APlayerCharacter::RecoveryStamina, timeToRecoveryStamina, true);
		}
	else
	{
		stamina = 0;
		SprintDisabled();
	}
}

void APlayerCharacter::RecoveryStamina()
{
	if (!sprint || axisX == 0)
	{
		if (stamina < 100)
			stamina++;
		else
		{
			return;
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_StaminaRecovery);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_StaminaDecrease, this, &APlayerCharacter::DecreaseStamina, timeToDecreaseStamina, true);
	}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::SprintEnabled()
{
	if (stamina > 0)
	{
		sprint = true;

		resSpeed = 600;
		GetCharacterMovement()->MaxWalkSpeed = resSpeed;

		if (GetWorld())
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_StaminaRecovery);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_StaminaDecrease, this, &APlayerCharacter::DecreaseStamina, timeToDecreaseStamina, true);
		}
	}
	else
	{
		SprintDisabled();
	}
}

void APlayerCharacter::SprintDisabled()
{
	sprint = false;

	resSpeed = 300;
	GetCharacterMovement()->MaxWalkSpeed = resSpeed;

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_StaminaDecrease);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_StaminaRecovery, this, &APlayerCharacter::RecoveryStamina, timeToRecoveryStamina, true);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovementTick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move"), this, &APlayerCharacter::InputAxisX);

	PlayerInputComponent->BindAction(TEXT("sprint"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SprintEnabled);
	PlayerInputComponent->BindAction(TEXT("sprint"), EInputEvent::IE_Released, this, &APlayerCharacter::SprintDisabled);
}

float APlayerCharacter::GetStamina()
{
	return stamina;
}

void APlayerCharacter::Death()
{
	//
}
