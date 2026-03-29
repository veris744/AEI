// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbilities/SprintGA.h"

#include "Characters/AEICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void USprintGA::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	AAEICharacter* Character = Cast<AAEICharacter>(GetOwningActorFromActorInfo());
	
	if (!Character)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}
	
	ToggleSprint(Character);
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void USprintGA::ToggleSprint(const AAEICharacter* Character)
{
	if (Character->GetCharacterMovement()->GetMaxSpeed() >= Character->SprintSpeed)
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = Character->WalkSpeed;
	}
	else
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = Character->SprintSpeed;
	}
}