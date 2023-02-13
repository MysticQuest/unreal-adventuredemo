// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioSource.h"

UAudioSource::UAudioSource()
{
	bAutoActivate = false;
}

void UAudioSource::PlaySound()
{
	UAudioComponent::Play();
}

void UAudioSource::PlayForSeconds(float PlayTime)
{
	PlaySound();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UAudioSource::StopSound, 1, false, PlayTime);
}

void UAudioSource::LoopForTimes(int32 NumLoops)
{

}

void UAudioSource::StopSound()
{
	UAudioComponent::Stop();
}
