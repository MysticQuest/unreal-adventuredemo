// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboLock.h"
#include "Movable.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

int UComboLock::Combo = 0;
int UComboLock::Pressed = 0;
AActor* UComboLock::SharedActor = nullptr;
TArray<UMovable*> UComboLock::AllMovables;
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

	UComboLock::Combo = 0;
	UComboLock::Pressed = 0;

	if (TriggerTarget) { SharedActor = TriggerTarget; }
	else { if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::Printf(TEXT("TriggerTarget for ComboLock has not been set!"))); } }

	MyMovable = GetOwner()->FindComponentByClass<UMovable>();
	MyMesh = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));
}


// Called every frame
void UComboLock::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UComboLock::ActivateButton()
{
	AllMovables.Add(MyMovable);
	AllMeshes.Add(MyMesh);

	GetOwner()->FindComponentByClass<UMovable>()->SetShouldMove(true);
	Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()))->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Ignore);

	IncrementPressed();
	if (IsCorrect) { IncrementCombo(); }

	if (UComboLock::Pressed > 7 && UComboLock::Combo < 8) { StaticReset(); }
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

void UComboLock::StaticReset()
{
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::Printf(TEXT("Wrong combination..."))); }

	UComboLock::Pressed = 0;
	UComboLock::Combo = 0;

	for (UStaticMeshComponent* Mesh : AllMeshes)
	{
		Mesh->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Ignore);
	}

	UWorld* World = GEngine->GetWorld(); //world is probs 0
	if (World == nullptr) 
	{ 
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::Printf(TEXT("world is ptrnull")));
		return;
	}
	World->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateLambda([&]()
		{
			FTimerHandle TimerHandle;
			World->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
				{
					for (UStaticMeshComponent* Mesh : AllMeshes)
					{
						Mesh->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
					}
					for (UMovable* Movable : AllMovables)
					{
						Movable->SetShouldMoveBack(true);
					}
				}), 1.0f, false);
		}));
}

void UComboLock::Unlock() 
{
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::Printf(TEXT("The door has been unlocked..."))); }
	SharedActor->FindComponentByClass<UMovable>()->SetShouldMove(true);
}