// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "AudioSource.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ADVENTUREDEMO_API UAudioSource : public UAudioComponent
{
	GENERATED_BODY()
	
public:
	UAudioSource();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extra Sounds")
		USoundBase* Sound_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extra Sounds")
		USoundBase* Sound_2;

	UFUNCTION(BlueprintCallable, Category = "Audio")
		void PlaySound();

	UFUNCTION(BlueprintCallable, Category = "Audio")
		void PlayForSeconds(float PlayTime);

	UFUNCTION(BlueprintCallable, Category = "Audio")
		void LoopForTimes(int32 NumLoops);

	UFUNCTION(BlueprintCallable, Category = "Audio")
		void StopSound();
};
