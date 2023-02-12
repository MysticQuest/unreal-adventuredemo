// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboLock.h"
#include "Movable.h"

int UComboLock::Combo = 0;
int UComboLock::Pressed = 0;

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
}


// Called every frame
void UComboLock::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::Printf(TEXT("how many buttons were pressed: %d"), UComboLock::Pressed));
	}
}

void UComboLock::Activate()
{

}

void UComboLock::IncrementPressed()
{
	UComboLock::Pressed++;
}

void UComboLock::IncrementCombo()
{
	UComboLock::Combo++;
}

void UComboLock::Reset() 
{
	UComboLock::Pressed = 0;
	UComboLock::Combo = 0;
}

void UComboLock::Unlock() 
{

}