// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabbable.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADVENTUREDEMO_API UGrabbable : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabbable();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void Release();

	UFUNCTION(BlueprintCallable)
		void Grab();

private: 
	UPROPERTY(EditAnywhere)
		float MaxGrabDistance = 130;

	UPROPERTY(EditAnywhere)
		float GrabRadius = 70;

	UPROPERTY(EditAnywhere)
		float GrabDistance = 100;

	bool CheckForGrabbable(FHitResult& OutHitResult) const;
	void AlignGrabbed();
	UPhysicsHandleComponent* PhysicsHandle;
};
