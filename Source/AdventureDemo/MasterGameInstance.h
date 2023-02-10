// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MasterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREDEMO_API UMasterGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMasterGameInstance();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
		FName GrabbedTag = "Grabbed";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
		FName SkeletonSkullTag = "JoinSkeleton";
};
