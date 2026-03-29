// Fill out your copyright notice in the Description page of Project Settings.


#include "FocusAT.h"

#include "Characters/AEICharacter.h"
#include "Interactable/Interactable.h"


UFocusAT* UFocusAT::CreateTask(UGameplayAbility* OwningAbility)
{
	UFocusAT* Task = NewAbilityTask<UFocusAT>(OwningAbility);
	
	return Task;
}

void UFocusAT::Activate()
{
	Super::Activate();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Task Activated"));
	
	// Checking that Player is running ability
	if(!OwningCharacter && Ability->GetOwningActorFromActorInfo()->IsA(AAEICharacter::StaticClass()))
	{
		OwningCharacter = Cast<AAEICharacter>(Ability->GetOwningActorFromActorInfo());
		if (!OwningCharacter)
		{
			OnCompleted.Broadcast();
			EndTask();
			return;
		}
		// Adding Confirm and Cancel events
		OwningCharacter->OnConfirm.AddDynamic(this, &UFocusAT::OnInteractConfirm);
		OwningCharacter->OnCancel.AddDynamic(this, &UFocusAT::OnInteractCancel);
	}
	else if (!OwningCharacter && !Ability->GetOwningActorFromActorInfo()->IsA(AAEICharacter::StaticClass()))
	{
		OnCompleted.Broadcast();
		EndTask();
	}

}

void UFocusAT::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	
	FHitResult HitResult;
	// Character is looking at interactable
	if (OwningCharacter->LookForInteractable(HitResult))
	{
		// Interactable was not already selected
		if (HitResult.GetActor() != FocusedActor)
		{
			// If there was a different, focused actor before, we cancel its action
			if (FocusedActor)
			{
				IInteractable::Execute_OnCancel(FocusedActor, OwningCharacter);
			}
			// We assign the new focused actor
			FocusedActor = HitResult.GetActor();
			IInteractable::Execute_OnFocus(HitResult.GetActor(), OwningCharacter);
		}
	}
	// Character is not looking at interactable
	else
	{
		// We remove previous focused actor if needed
		if (FocusedActor)
		{
			IInteractable::Execute_OnCancel(FocusedActor, OwningCharacter);
			FocusedActor = nullptr;
		}
	}

}

void UFocusAT::OnInteractConfirm()
{
	if (FocusedActor)
	{
		// Trigger Interactable Action
		IInteractable::Execute_OnConfirm(FocusedActor, OwningCharacter);
	}
	// End task
	OnCompleted.Broadcast();
	EndTask();
}

void UFocusAT::OnInteractCancel()
{
	if (FocusedActor)
	{
		// Cancel Interactable Action
		IInteractable::Execute_OnCancel(FocusedActor, OwningCharacter);
	}
	// End task
	OnCompleted.Broadcast();
	EndTask();
}

