// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystem/AbilityBinding.h"
#include "AEICharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);


/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class AAEICharacter : public ACharacter
{
	GENERATED_BODY()
	
	/////////////////////////////////////////////////////////////
	///	CHARACTER COMPONENTS 	/////////////////////////////////
	/////////////////////////////////////////////////////////////

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	/////////////////////////////////////////////////////////////
	///	GAME FLOW 	/////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	
	AAEICharacter();	
	
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void BeginPlay() override;

	
	/////////////////////////////////////////////////////////////
	///	INPUT 	/////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	// INPUT ACTIONS
	
	/** Interact Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InteractAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;
	
	/** Confirm Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* ConfirmAction;
	
	/** Cancel Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* CancelAction;
	
	/** Cancel Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* SprintAction;
	
protected:
	
	// INPUT FUNCTIONS
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles Interact pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void Interact();
	
	/** Handles Interact pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void Confirm();
	
	/** Handles Interact pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void Cancel();
	
	/** Handles Interact pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void Sprint();
	
	
public:
	
	/////////////////////////////////////////////////////////////
	///	STATS 	/////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	
	UPROPERTY(EditAnywhere, Category="Stats")
	float SprintSpeed = 600;
	float WalkSpeed = 400;
	
	/////////////////////////////////////////////////////////////
	///	ABILITY SYSTEM	/////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	
	UPROPERTY(VisibleAnywhere, Category="Abilities")
	class UMainASC* ASC;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Abilities")
	TArray<FAbilityBinding> DefaultAbilities;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FConfirmDelegate);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCancelDelegate);
	
	UPROPERTY()
	FConfirmDelegate OnConfirm;
	UPROPERTY()
	FCancelDelegate OnCancel;
	
	
	
	/////////////////////////////////////////////////////////////
	///	INTERACT SYSTEM	/////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	
private:
	UPROPERTY()
	AActor* FocusedInteractable = nullptr;
	
public:
	UFUNCTION(BlueprintCallable, Category="Interactable")
	bool LookForInteractable(FHitResult& HitResult) const;
};

