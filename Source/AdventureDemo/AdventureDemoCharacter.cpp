// Copyright Epic Games, Inc. All Rights Reserved.

#include "AdventureDemoCharacter.h"
#include "AdventureDemoProjectile.h"
#include "Animation/AnimInstance.h"
#include "Blueprint/UserWidget.h"
#include "Components/Widget.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "UMG/Public/Animation/WidgetAnimation.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


//////////////////////////////////////////////////////////////////////////
// AAdventureDemoCharacter

AAdventureDemoCharacter::AAdventureDemoCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	// Creates the widget reference instead of exposing it to the editor as was the case with the UI widget, for variety
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

void AAdventureDemoCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	Grabbable = Cast<UGrabbable>(GetComponentByClass(UGrabbable::StaticClass()));
	DotWidget = CreateWidget<UUserWidget>(GetWorld(), DotWidgetClass);
	DotWidget->AddToViewport();

	MyAudio = this->FindComponentByClass<UAudioSource>();
	if (MyAudio) { MyAudio->Super::FadeIn(3, MyAudio->Super::GetSound()->GetVolumeMultiplier(), 0, EAudioFaderCurve::Linear); }

	ShowLoadingWidget();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAdventureDemoCharacter::AnimateLoadingWidget, 1, false, 3);
}

//////////////////////////////////////////////////////////////////////////// Input

void AAdventureDemoCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAdventureDemoCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAdventureDemoCharacter::Look);

		InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &AAdventureDemoCharacter::OnGrabPressed);
	}
}

void AAdventureDemoCharacter::OnGrabPressed()
{
	if (!Grabbable->IsGrabbing()) { Grabbable->Grab(); }
	else { Grabbable->Release(); }
}

void AAdventureDemoCharacter::ShowLoadingWidget()
{
	if (!LoadingWidget && LoadingWidgetClass)
	{
		LoadingWidget = CreateWidget<UUserWidget>(GetWorld(), LoadingWidgetClass);
		if (LoadingWidget)
		{
			LoadingWidget->AddToViewport();
			BPLoadingWidgetClass = LoadingWidget->GetWidgetTreeOwningClass();
		}
	}
}

void AAdventureDemoCharacter::AnimateLoadingWidget()
{
	if (LoadingWidget)
	{
		if (BPLoadingWidgetClass->Animations[0] != nullptr)
		{
			LoadingWidget->PlayAnimationForward(BPLoadingWidgetClass->Animations[0], 1, false);
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAdventureDemoCharacter::CleanLoadingWidget, 1, false, 3);
		}
		else 
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "LoadingWidget animation not found!");
		}
	}
}

void AAdventureDemoCharacter::CleanLoadingWidget()
{
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	LoadingWidget->RemoveFromParent();
	LoadingWidget = nullptr;
}

void AAdventureDemoCharacter::ManageUIWidget()
{
	if (!Grabbable || !DotWidget) { return; }
	FHitResult HitResult;
	if (Grabbable->CheckForGrabbable(HitResult) && !Grabbable->IsGrabbing())
	{
		DotWidget->SetColorAndOpacity(FLinearColor(1,1,1,.5f));
	}
	else { DotWidget->SetColorAndOpacity(FLinearColor(1, 1, 1, 0)); }
}


void AAdventureDemoCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AAdventureDemoCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AAdventureDemoCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AAdventureDemoCharacter::GetHasRifle()
{
	return bHasRifle;
}