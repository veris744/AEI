// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Characters/AEICharacter.h"
#include "FocusAT.generated.h"

/**
 * 
 */
UCLASS()
class AEI_API UFocusAT : public UAbilityTask
{
	GENERATED_BODY()
	
	UPROPERTY()
	AAEICharacter* OwningCharacter;
	
	UPROPERTY()
	AActor* FocusedActor;
	
	UFocusAT()
	{
		bTickingTask = true;
	};
	
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMyTaskDelegate);
	
	UPROPERTY(BlueprintAssignable)
	FMyTaskDelegate OnCompleted;
	
	static UFocusAT* CreateTask(UGameplayAbility* OwningAbility);
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	
	UFUNCTION()
	void OnInteractConfirm();
	UFUNCTION()
	void OnInteractCancel();
};
