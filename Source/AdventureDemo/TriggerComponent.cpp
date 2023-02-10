// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	Movable = TriggerTarget->FindComponentByClass<UMovable>();
}

void UTriggerComponent::TickComponent(
	float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	OverlapTrigger();
}

void UTriggerComponent::OverlapTrigger()
{
	OverlappingActor = GetOverlappingActor();
	if (Movable != nullptr && OverlappingActor != nullptr)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(OverlappingActor->GetRootComponent());
		if (Component != nullptr)
		{
			Component->SetSimulatePhysics(false);
		}
		OverlappingActor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		Movable->SetShouldMove(true);
	}
	else { Movable->SetShouldMove(false); };
}

AActor* UTriggerComponent::GetOverlappingActor() const
{
	AActor* NoActor = nullptr;
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

		for (AActor* Actor : Actors)
		{
			if (Actor->ActorHasTag(TriggerTag) && !Actor->ActorHasTag("Grabbed"))
			{ 
				return Actor;
			}
		}
		return NoActor;
}

