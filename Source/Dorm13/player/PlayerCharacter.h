// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipBook.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFoodThroughted);

class UHealthComponent;
class UInventoryComponent;
class IInteractableItem;
class AAIntractableObject;
class AFood;

UCLASS()
class DORM13_API APlayerCharacter : public APaperCharacter
{
	GENERATED_BODY()
	
private:
	UPaperFlipbookComponent* flipBookComponent;
	float axisX = 0.0f;
	bool sprint = false;
	float resSpeed = 300.f;

	float stamina = 100.f;
	float timeToDecreaseStamina = 0.1f;
	float timeToRecoveryStamina = 0.15f;
	FTimerHandle TimerHandle_StaminaDecrease;
	FTimerHandle TimerHandle_StaminaRecovery;

	class AAInteractableObject* objectToInteract = nullptr;

	void InputAxisX(float value);
	void MovementTick(float deltaSeconds);

	void DecreaseStamina();
	void RecoveryStamina();

protected:
	TArray<class AFood*> foodInWorld;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UPaperFlipbook* idleAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UPaperFlipbook* walkAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UPaperFlipbook* runAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	class UInventoryComponent* inventory;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 currentItemIndex = 0;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SprintEnabled();
	void SprintDisabled();

public:
	UPROPERTY()
	FOnFoodThroughted OnFoodThroughted;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* healthComponent;

	APlayerCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	float GetStamina();
	void IncreaseStamina(float valueToIncrease);

	void Death();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	void InteractWithObject();
	void TakeItemToInventory();
	UFUNCTION(BlueprintCallable)
	void UseItem();

	void ThroughtFood();
	void DecreaseHealth();

	void AddFoodToWorld(AFood* food);
	void RemoveFoodFfromWorld(AFood* food);
	TArray<AFood*> GetFood();
};
