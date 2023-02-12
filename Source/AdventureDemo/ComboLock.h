// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Movable.h"
#include "ComboLock.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADVENTUREDEMO_API UComboLock : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComboLock();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere)
		bool IsCorrect = false;

	void ActivateButton();

private:

	static int Combo;
	static int Pressed;
	static TArray<UMovable*> AllMovables;
	static TArray<UStaticMeshComponent*> AllMeshes;

	UMovable* MyMovable;
	UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere)
		AActor* TriggerTarget;

	static AActor* SharedActor;

	void IncrementCombo();
	void IncrementPressed();
	void Unlock();
	static void StaticReset();
};
