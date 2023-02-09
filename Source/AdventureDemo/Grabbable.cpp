// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabbable.h"

// Sets default values for this component's properties
UGrabbable::UGrabbable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabbable::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}


// Called every frame
void UGrabbable::TickComponent(
	float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AlignGrabbed();
}

void UGrabbable::Grab()
{
	if (PhysicsHandle == nullptr) { return; }

	if (CheckForGrabbable())
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation
		(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("::: " + HitActor->GetActorNameOrLabel()));
	}
}

bool UGrabbable::CheckForGrabbable()
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;

	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(
		HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, CollisionShape);
}

void UGrabbable::AlignGrabbed()
{
	if (PhysicsHandle == nullptr) { return; }

	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * GrabDistance;
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
}

void UGrabbable::Release()
{

}
