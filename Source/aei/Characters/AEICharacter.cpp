// Copyright Epic Games, Inc. All Rights Reserved.

#include "AEICharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "aei.h"
#include "AbilitySystem/MainASC.h"
#include "Interactable/Interactable.h"

AAEICharacter::AAEICharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	
	// Initialize AbilitySystemComponent (ASC)
	ASC = CreateDefaultSubobject<UMainASC>(TEXT("AbilitySystemComponent"));
	ASC->SetIsReplicated(false);
}

void AAEICharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (ASC)
	{
		ASC->InitAbilityActorInfo(this, this);
	}

	// ASC MixedMode replication requires that the ASC Owner's Owner be the Controller.
	SetOwner(NewController);
}

void AAEICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (ASC)
	{
		for (const FAbilityBinding& Binding : DefaultAbilities)
		{
			if (Binding.Ability)
			{
				ASC->GiveAbility(FGameplayAbilitySpec(
					Binding.Ability,
					Binding.Level,
					static_cast<int32>(Binding.InputID),
					this
				));
			}
		}
	}
}

void AAEICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Interacting, confirming and canceling
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AAEICharacter::Interact);
		EnhancedInputComponent->BindAction(ConfirmAction, ETriggerEvent::Triggered, this, &AAEICharacter::Confirm);
		EnhancedInputComponent->BindAction(CancelAction, ETriggerEvent::Triggered, this, &AAEICharacter::Cancel);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAEICharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AAEICharacter::Look);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AAEICharacter::Sprint);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAEICharacter::Look);
		
	}
	else
	{
		UE_LOG(Logaei, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AAEICharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AAEICharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AAEICharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AAEICharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AAEICharacter::Interact()
{
	if (ASC)
	{
		ASC->AbilityLocalInputPressed(
			static_cast<int32>(EGASAbilityInputID::Interact)
		);
	}
}

void AAEICharacter::Confirm()
{
	OnConfirm.Broadcast();
}

void AAEICharacter::Cancel()
{
	OnCancel.Broadcast();
}

void AAEICharacter::Sprint()
{
	if (ASC)
	{
		ASC->AbilityLocalInputPressed(
			static_cast<int32>(EGASAbilityInputID::Sprint)
		);
	}
}


bool AAEICharacter::LookForInteractable(FHitResult& HitResult) const 
{
	GetWorld()->LineTraceSingleByChannel(
		HitResult,		
		FollowCamera->GetComponentLocation(),
		FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector() * 10000.0,
		ECC_GameTraceChannel1
	);
	//DrawDebugLine(GetWorld(),FollowCamera->GetComponentLocation(),FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector() * 1000.0, FColor::Red);
	
	if (!HitResult.GetActor() || !HitResult.GetActor()->Implements<UInteractable>())
	{
		HitResult = FHitResult();
		return false;
	}
	
	return HitResult.bBlockingHit;
}

