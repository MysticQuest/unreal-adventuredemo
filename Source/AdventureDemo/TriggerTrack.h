// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "AudioSource.h"
#include "TriggerTrack.generated.h"


UCLASS()
class ADVENTUREDEMO_API ATriggerTrack : public ATriggerBox
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ATriggerTrack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
		USoundBase* MyTriggerSound;

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	
	void SetSound();

	UAudioSource* CharAudio;
	ACharacter* MyCharacter;
};
