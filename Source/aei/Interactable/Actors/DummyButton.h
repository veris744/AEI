// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable/Interactable.h"
#include "DummyButton.generated.h"

UCLASS()
class AEI_API ADummyButton : public AActor, public IInteractable
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* DynMaterial;

public:
	ADummyButton();
	
	virtual void BeginPlay() override;
	
	virtual void OnFocus_Implementation(AActor* Actor) override;
	virtual void OnConfirm_Implementation(AActor* Actor) override;
	virtual void OnCancel_Implementation(AActor* Actor) override;

};
