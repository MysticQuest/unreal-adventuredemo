// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "MasterGameInstance.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ADVENTUREDEMO_API UMasterGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMasterGameInstance();
	virtual void OnStart() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
		FName InteractableTag = "Interactable";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
		FName GrabbableTag = "Grabbable";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
		FName GrabbedTag = "Grabbed";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
		FName SkeletonSkullTag = "JoinSkeleton";

	TSubclassOf<UUserWidget> LoadingWidgetClass;

private:

	UUserWidget* LoadingWidget;
};
