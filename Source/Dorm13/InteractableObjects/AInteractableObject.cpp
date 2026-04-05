// Fill out your copyright notice in the Description page of Project Settings.


#include "AInteractableObject.h"
#include "Components/BoxComponent.h"
#include "Dorm13/player/PlayerCharacter.h"


AAInteractableObject::AAInteractableObject()
{
	itemName = NAME_None;

	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	boxCollision->SetupAttachment(RootComponent);

	if (GetRenderComponent() && GetRenderComponent()->GetFlipbook())
	{
		FVector spriteSize = GetRenderComponent()->Bounds.BoxExtent;
		boxCollision->SetBoxExtent(spriteSize);
	}
	else
		boxCollision->SetBoxExtent(FVector(32.f, 32.f, 10.f));

	boxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	boxCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	boxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	boxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}
