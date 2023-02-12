// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabbable.h"
#include "Kismet/GameplayStatics.h"

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

	MasterGameInstance = Cast<UMasterGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}


// Called every frame
void UGrabbable::TickComponent(
	float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AlignGrabbed();
}

bool UGrabbable::CheckForGrabbable(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;

	FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(GrabCapsuleRadius, GrabCapsuleHalfHeight);
	return GetWorld()->SweepSingleByChannel(
		OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, CollisionShape);
}

void UGrabbable::Grab()
{
	if (PhysicsHandle == nullptr) { return; }

	FHitResult HitResult;
	if (CheckForGrabbable(HitResult))
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		OverlappingActor = HitResult.GetActor();

		if (OverlappingActor->Tags.Contains(MasterGameInstance->GrabbableTag))
		{
			OverlappingActor->Tags.Add(MasterGameInstance->GrabbedTag);
			PhysicsHandle->GrabComponentAtLocationWithRotation
			(
				HitComponent,
				NAME_None,
				HitResult.ImpactPoint,
				GetComponentRotation()
			);
		}
		// Class should be called interactable for better categorization between use/grab
		else if (OverlappingActor->Tags.Contains(MasterGameInstance->InteractableTag))
		{
			UComboLock* ComboComp = OverlappingActor->FindComponentByClass<UComboLock>();
			ComboComp->ActivateButton();
		}
	}
}

bool UGrabbable::IsGrabbing()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::Printf(TEXT("Bool: %s"), PhysicsHandle && PhysicsHandle->GetGrabbedComponent() ? TEXT("true") : TEXT("false")));
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent()) { return true; }
	else { return false; }
}

void UGrabbable::AlignGrabbed()
{
	if (IsGrabbing())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * GrabDistance;
		PhysicsHandle->SetTargetLocationAndRotation(
			TargetLocation, GetComponentRotation()
		);
	}
}

void UGrabbable::Release()
{
	if (IsGrabbing())
	{
		AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedActor->Tags.Remove(MasterGameInstance->GrabbedTag);
		PhysicsHandle->ReleaseComponent(); 
	}
}
