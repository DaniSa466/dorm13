// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNPCCharacter1.h"
#include "GameFramework/CharacterMovementComponent.h"

void ABaseNPCCharacter::BeginPlay()
{
	baseLocation = GetActorLocation();
	destination = GetActorLocation();

	npcController = Cast<ANPCController>(GetController());
}

void ABaseNPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float distanceToDestination = FMath::Abs(GetActorLocation().X - destination.X);
	if (distanceToDestination < 10.f)
		OnDestinationReached.ExecuteIfBound();

	//AddMovementInput(FVector(1.f, 0.f, 0.f), 1.f);
	UE_LOG(LogTemp, Warning, TEXT("MAxWalkSpeed NPC - %f"), GetCharacterMovement()->MaxWalkSpeed);
	UE_LOG(LogTemp, Warning, TEXT("distance between player and NPC is %f"), GetCharacterMovement()->MaxWalkSpeed);
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

void ABaseNPCCharacter::SetRotation(float side)
{
	if (side > 0)
		flipBookComponent->SetWorldRotation(FRotator(0.f, 180.f, 0.f));
	if (side < 0)
		flipBookComponent->SetWorldRotation(FRotator(0.f, 0.f, 0.f));
}

UPaperFlipbook* ABaseNPCCharacter::GetAnimToPlay(FString stateName)
{
	if (stateName == "idle")
		return idleAnimation;
	else if (stateName == "chase")
		return chaseAnimation;
	else if (stateName == "wander")
		return wanderAnimation;
	else
		return nullptr;
}

void ABaseNPCCharacter::MoveActor(float move)
{
	float newX = GetActorLocation().X + move;
	destination = FVector(newX, 0.f, 0.f);

	float directionX = (move > 0) ? 1.f : -1.f;
	FVector direction = FVector(directionX, 0.f, 0.f);
	AddMovementInput(direction, 1.f);
}

bool ABaseNPCCharacter::CheckCanMove(float moveSide)
{
	return FMath::Abs(GetActorLocation().X - baseLocation.X + moveSide) < maxDeviation;
}
