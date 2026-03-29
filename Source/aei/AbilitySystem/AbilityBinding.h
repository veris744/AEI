// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityBinding.generated.h"

UENUM(BlueprintType)
enum class EGASAbilityInputID : uint8
{
	None		UMETA(DisplayName = "None"),
	Interact	UMETA(DisplayName = "Interact"),
	Sprint		UMETA(DisplayName = "Sprint")
};

USTRUCT(BlueprintType)
struct FAbilityBinding
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> Ability;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EGASAbilityInputID InputID = EGASAbilityInputID::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Level = 1;
};