// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerBoxRestart.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

ATriggerBoxRestart::ATriggerBoxRestart()
{
	OnActorBeginOverlap.AddDynamic(this, &ATriggerBoxRestart::OnOverlapBegin);
}

void ATriggerBoxRestart::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor)
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
	}
}


