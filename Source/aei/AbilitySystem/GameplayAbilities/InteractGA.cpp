// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbilities/InteractGA.h"

#include "AbilitySystem/AbilityTasks/FocusAT.h"

void UInteractGA::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	UFocusAT* Task = UFocusAT::CreateTask(this);
	Task->OnCompleted.AddDynamic(this, &UInteractGA::OnTaskCompleted);
	Task->ReadyForActivation();

	Task->Activate();
}

void UInteractGA::OnTaskCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}
