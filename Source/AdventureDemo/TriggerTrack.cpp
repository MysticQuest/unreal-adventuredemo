// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerTrack.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
ATriggerTrack::ATriggerTrack()
{
	OnActorBeginOverlap.AddDynamic(this, &ATriggerTrack::OnOverlapBegin);
}

void ATriggerTrack::BeginPlay()
{
	Super::BeginPlay();
	
	MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (MyCharacter) { CharAudio = MyCharacter->FindComponentByClass<UAudioSource>(); }
}

void ATriggerTrack::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && MyTriggerSound != CharAudio->Super::GetSound())
	{
		CharAudio->Super::FadeOut(3, 0, EAudioFaderCurve::Linear);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATriggerTrack::SetSound, 1, false, 2);
	}
}

void ATriggerTrack::SetSound()
{
	CharAudio->Super::SetSound(MyTriggerSound);
	CharAudio->Super::FadeIn(3, MyTriggerSound->GetVolumeMultiplier(), 0, EAudioFaderCurve::Linear);
}

