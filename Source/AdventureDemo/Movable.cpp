// Fill out your copyright notice in the Description page of Project Settings.


#include "Movable.h"


// Sets default values for this component's properties
UMovable::UMovable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMovable::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetOwner()->GetActorLocation();
	MyAudio = GetOwner()->FindComponentByClass<UAudioSource>();
}


// Called every frame
void UMovable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector TargetLocation = InitialLocation + MoveOffset;
	float Speed = FVector::Distance(InitialLocation, TargetLocation) / MoveDuration;
	FVector CurrentLocation = GetOwner()->GetActorLocation();

	if (ShouldMove)
	{
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		GetOwner()->SetActorLocation(NewLocation);
	}

	if (ShouldMoveBack)
	{	
		FVector StartingLocation = FMath::VInterpConstantTo(CurrentLocation, InitialLocation, DeltaTime, Speed);
		GetOwner()->SetActorLocation(StartingLocation);
	}
}

void UMovable::SetShouldMove(bool _ShouldMove)
{
	if (_ShouldMove) { PlaySoundEffect(MoveDuration); }
	ShouldMove = _ShouldMove;
	ShouldMoveBack = false;
}

void UMovable::SetShouldMoveBack(bool _ShouldMoveBack)
{
	if (_ShouldMoveBack) { PlaySoundEffect(MoveDuration); }
	ShouldMoveBack = _ShouldMoveBack;
	ShouldMove = false;
}

void UMovable::PlaySoundEffect(float duration) {
	MyAudio->PlayForSeconds(duration);
}
