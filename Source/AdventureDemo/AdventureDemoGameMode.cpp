// Copyright Epic Games, Inc. All Rights Reserved.

#include "AdventureDemoGameMode.h"
#include "AdventureDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAdventureDemoGameMode::AAdventureDemoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
