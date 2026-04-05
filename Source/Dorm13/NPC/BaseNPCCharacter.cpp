// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNPCCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void ABaseNPCCharacter::BeginPlay()
{
	Super::BeginPlay();

	baseLocation = GetActorLocation();
	destination = GetActorLocation();

	npcController = Cast<ANPCController>(GetController());
}

void ABaseNPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float distanceToDestination = FMath::Abs(GetActorLocation().X - destination.X);
	if (distanceToDestination < 10.f)
	{
		OnDestinationReached.ExecuteIfBound();
		direction = FVector(0.f, 0.f, 0.f);
		flipBookComponent->SetFlipbook(idleAnimation);
	}

	AddMovementInput(direction, 1.f);
}

ABaseNPCCharacter::ABaseNPCCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	flipBookComponent = GetSprite();
	flipBookComponent->SetLooping(true);

	GetCharacterMovement()->MaxWalkSpeed = resSpeed;
}

void ABaseNPCCharacter::PlayAnim(UPaperFlipbook* anim)
{
	flipBookComponent->SetFlipbook(anim);
}

void ABaseNPCCharacter::PlayAnimOnce(UPaperFlipbook* anim)
{
	flipBookComponent->SetFlipbook(anim);
	flipBookComponent->SetLooping(false);
	flipBookComponent->PlayFromStart();
}

UPaperFlipbook* ABaseNPCCharacter::GetAnimToPlay(FString stateName)
{
	if (stateName == "idle")
		return idleAnimation;
	else if (stateName == "chase")
		return chaseAnimation;
	else if (stateName == "wander")
		return wanderAnimation;
	else if (stateName == "attack")
		return hitAnimation;
	else
		return nullptr;
}

void ABaseNPCCharacter::MoveActor(float move)
{
	float newX = GetActorLocation().X + move;
	destination = FVector(newX, 0.f, 0.f);

	float directionX = (move > 0) ? 1.f : -1.f;
	direction = FVector(directionX, 0.f, 0.f);

	if (directionX > 0)
		flipBookComponent->SetWorldRotation(FRotator(0.f, 180.f, 0.f));
	else
		flipBookComponent->SetWorldRotation(FRotator(0.f, 0.f, 0.f));
}

bool ABaseNPCCharacter::CheckCanMove(float moveSide)
{
	return FMath::Abs(GetActorLocation().X - baseLocation.X + moveSide) < maxDeviation;
}

void ABaseNPCCharacter::UnsetDestination()
{
	destination = FVector(0.f, 300.f, 0.f);
}

