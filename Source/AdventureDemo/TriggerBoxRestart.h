
#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerBoxRestart.generated.h"

UCLASS()
class ADVENTUREDEMO_API ATriggerBoxRestart : public ATriggerBox
{
	GENERATED_BODY()

public:
	ATriggerBoxRestart();

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
};

