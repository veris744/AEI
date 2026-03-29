#pragma once
#include "Interactable.generated.h"

UINTERFACE(Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
	
public:
	
};

class IInteractable
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void OnFocus(AActor* Actor);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void OnConfirm(AActor* Actor);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void OnCancel(AActor* Actor);
};