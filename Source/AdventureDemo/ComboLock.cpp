// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboLock.h"
#include "Movable.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

int UComboLock::Combo = 0;
int UComboLock::Pressed = 0;
AActor* UComboLock::SharedActor = nullptr;
TArray<UMovable*> UComboLock::ActivatedMovables;
TArray<UStaticMeshComponent*> UComboLock::AllMeshes;

// Sets default values for this component's properties
UComboLock::UComboLock()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UComboLock::BeginPlay()
{
	Super::BeginPlay();

	if (TriggerTarget) { SharedActor = TriggerTarget; }
	else { if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::Printf(TEXT("TriggerTarget for ComboLock has not been set!"))); } }

	MyMovable = GetOwner()->FindComponentByClass<UMovable>();
	MyMesh = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	AllMeshes.Add(MyMesh);
}


// Called every frame
void UComboLock::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UComboLock::ActivateButton()
{
	ActivatedMovables.Add(MyMovable);

	MyMovable->SetShouldMove(true);
	MyMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Ignore);

	IncrementPressed();
	if (IsCorrect) { IncrementCombo(); }

	if (UComboLock::Pressed > 7 && UComboLock::Combo < 8) { Reset(GetOwner()->GetWorld()); }
	else if ( UComboLock::Combo > 7 ) { Unlock(); }
}

void UComboLock::IncrementPressed()
{
	UComboLock::Pressed++;
}

void UComboLock::IncrementCombo()
{
	UComboLock::Combo++;
}

void UComboLock::Reset(UWorld* zeWorld)
{
	UComboLock::Pressed = 0;
	UComboLock::Combo = 0;

	DeactivateTriggers();
	GetWorld()->GetTimerManager().SetTimer(ResetTimerHandle, this, &UComboLock::ReactivateTriggers, 2, false, 2);
}

void UComboLock::DeactivateTriggers()
{
	for (UStaticMeshComponent* Mesh : AllMeshes)
	{
		Mesh->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Ignore);
	}
}

void UComboLock::ReactivateTriggers()
{
	for (UStaticMeshComponent* Mesh : AllMeshes)
	{
		Mesh->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);
	}
	for (UMovable* Movable : ActivatedMovables)
	{
		Movable->SetShouldMoveBack(true);
	}
}

void UComboLock::Unlock() 
{
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::Printf(TEXT("The door has been unlocked..."))); }
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UComboLock::OpenDoor, 1, false, 4);
	DeactivateTriggers();
}

void UComboLock::OpenDoor()
{
	SharedActor->FindComponentByClass<UMovable>()->SetShouldMove(true);
}

void UComboLock::ResetStatics()
{
	UComboLock::Pressed = 0;
	UComboLock::Combo = 0;
	ActivatedMovables.Empty();
	AllMeshes.Empty();
}