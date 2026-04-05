// Fill out your copyright notice in the Description page of Project Settings.


#include "Dorm13/player/PlayerCharacter.h"
#include "Dorm13/Components/HealthComponent.h"
#include "Dorm13/Components/InventoryComponent.h"
#include "Dorm13/InteractableObjects/InteractionItem.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Dorm13/InteractableObjects/InteractableItem.h"
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
	{
		if (sprint)
			flipBookComponent->SetFlipbook(runAnimation);
		else
			flipBookComponent->SetFlipbook(walkAnimation);
	}
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
	PlayerInputComponent->BindAction(TEXT("takeItem"), EInputEvent::IE_Released, this, &APlayerCharacter::InteractWithObject);
	PlayerInputComponent->BindAction(TEXT("useItem"), EInputEvent::IE_Released, this, &APlayerCharacter::UseItem);
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

	UE_LOG(LogTemp, Warning, TEXT("APlayerCharacter::IncreaseStamina"));
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
	objectToInteract = Cast<AAInteractableObject>(OtherActor);
}

void APlayerCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	objectToInteract = nullptr;
}

void APlayerCharacter::InteractWithObject()
{
	if (objectToInteract)
	{
		objectToInteract->SetPointerToChar(this);
		objectToInteract->Execute();
	}
}

void APlayerCharacter::TakeItemToInventory()
{
	if (objectToInteract)
	{
		IInteractableItem* itemToTake = Cast<IInteractableItem>(objectToInteract);
		if (itemToTake && inventory->GetMaxInventoryLenght() > inventory->GetInventoryLenght())
		{
			inventory->AddItemToInventory(itemToTake);
		}
		objectToInteract->Destroy();
	}
}

void APlayerCharacter::UseItem()
{
	IInteractableItem* itemToUse;
	itemToUse = inventory->GetItemByIndex(currentItemIndex);

	if (itemToUse)
	{
		itemToUse->UseItem();
		inventory->RemoveItemFromInventory(itemToUse);
	}
}

void APlayerCharacter::ThroughtFood()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter:: throught food"));
	OnFoodThroughted.Broadcast();
}

void APlayerCharacter::DecreaseHealth()
{
	healthComponent->MinusHeart();

	if (healthComponent->GetHearts() <= 0)
		Death();
}

void APlayerCharacter::AddFoodToWorld(AFood* food)
{
	foodInWorld.Add(food);
}

void APlayerCharacter::RemoveFoodFfromWorld(AFood* food)
{
	foodInWorld.Remove(food);
}

TArray<AFood*> APlayerCharacter::GetFood()
{
	return foodInWorld;
}

