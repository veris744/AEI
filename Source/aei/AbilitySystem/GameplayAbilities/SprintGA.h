// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SprintGA.generated.h"

class AAEICharacter;
/**
 * 
 */
UCLASS()
class AEI_API USprintGA : public UGameplayAbility
{
	GENERATED_BODY()

	static void ToggleSprint(const AAEICharacter* Character);
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;	

};
