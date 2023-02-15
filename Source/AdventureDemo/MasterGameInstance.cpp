// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterGameInstance.h"
#include "AdventureDemoCharacter.h"
#include "ComboLock.h"

UMasterGameInstance::UMasterGameInstance() 
{
	LoadingWidgetClass = nullptr;
	LoadingWidget = nullptr;

	LoadingWidget = CreateDefaultSubobject<UUserWidget>("Widget");
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetObject(TEXT("/Game/Widgets/LoadingWidget"));
	if (WidgetObject.Succeeded()) {
		LoadingWidgetClass = WidgetObject.Class;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "LoadingWidget not found!");
		LoadingWidgetClass = nullptr;
	}
}

void UMasterGameInstance::OnStart()
{
    Super::OnStart();
    UComboLock::ResetStatics();
}