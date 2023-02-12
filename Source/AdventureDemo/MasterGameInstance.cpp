// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterGameInstance.h"
#include "ComboLock.h"

UMasterGameInstance::UMasterGameInstance() {}

void UMasterGameInstance::OnStart()
{
    Super::OnStart();
    UComboLock::Pressed = 0;
}