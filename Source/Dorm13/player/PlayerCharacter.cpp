// Fill out your copyright notice in the Description page of Project Settings.


#include "Dorm13/player/PlayerCharacter.h"
#include "Dorm13/Components/HealthComponent.h"
#include "Dorm13/Components/InventoryComponent.h"
#include "Dorm13/InteractableObjects/InteractionItem.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	flipBookComponent = GetSprite();

	flipBookComponent->SetLooping(true);

	inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	if (healthComponent)
		healthComponent->OnDead.AddDynamic(this, &APlayerCharacter::Death);

	GetCharacterMovement()->MaxWalkSpeed = resSpeed;

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);
		GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnEndOverlap);
	}
}

void APlayerCharacter::InputAxisX(float value)
{
	axisX = value;
}

void APlayerCharacter::MovementTick(float deltaTime)
{
	if (axisX > 0)
		flipBookComponent->SetWorldRotation(FRotator(0.f, 180.f, 0.f));
	if (axisX < 0)
		flipBookComponent->SetWorldRotation(FRotator(0.f, 0.f, 0.f));

	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), axisX);

	if (axisX != 0)
		flipBookComponent->SetFlipbook(walkAnimation);
	else
		flipBookComponent->SetFlipbook(idleAnimation);
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

	flipBookComponent->SetWorldRotation(FRotator(0.f, 180.f, 0.f));
	flipBookComponent->SetFlipbook(idleAnimation);
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

void APlayerCharacter::TakeItemToInventory()
{
	if (itemToTake && inventory->GetMaxInventoryLenght() > inventory->GetInventoryLenght())
		inventory->AddItemToInventory(itemToTake);
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
	PlayerInputComponent->BindAction(TEXT("takeItem"), EInputEvent::IE_Released, this, &APlayerCharacter::TakeItemToInventory);
}

float APlayerCharacter::GetStamina()
{
	return stamina;
}

void APlayerCharacter::IncreaseStamina(float valueToIncrease)
{
	if (stamina + valueToIncrease <= 100)
		stamina += valueToIncrease;
	else
		stamina = 100;
}

void APlayerCharacter::Death()
{
	//
}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	itemToTake = Cast<AAInteractionItem>(OtherActor);
}

void APlayerCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	itemToTake = nullptr;
}