// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Movable.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADVENTUREDEMO_API UMovable : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovable();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetShouldMove(bool ShouldMove);
	void SetShouldMoveBack(bool ShouldMoveBack);

private:
	UPROPERTY(EditAnywhere)
		FVector MoveOffset = FVector(0, 0, 400);

	UPROPERTY(EditAnywhere)
		float MoveDuration = 4;

	UPROPERTY(EditAnywhere)
	bool ShouldMove = false;

	UPROPERTY(EditAnywhere)
	bool ShouldMoveBack = false;

	FVector InitialLocation;
		
};
