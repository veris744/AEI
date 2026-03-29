// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/Actors/DummyButton.h"


ADummyButton::ADummyButton()
{
	
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(SphereMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> SphereMat(TEXT("/Game/LevelPrototyping/Materials/M_Sphere1.M_Sphere1"));
	if (SphereMat.Succeeded())
	{
		MeshComponent->SetMaterial(0, SphereMat.Object);
	}

	MeshComponent->SetRelativeScale3D(FVector(2.5f));
}

void ADummyButton::BeginPlay()
{
	Super::BeginPlay();
	
	if (MeshComponent && MeshComponent->GetMaterial(0))
	{
		UMaterialInterface* Material = MeshComponent->GetMaterial(0);

		DynMaterial = MeshComponent->CreateAndSetMaterialInstanceDynamic(0);
		if (DynMaterial)
		{
			DynMaterial->SetVectorParameterValue("BaseColor", FLinearColor::White);

		}
	}
}

void ADummyButton::OnFocus_Implementation(AActor* Actor)
{
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("BaseColor", FLinearColor::Yellow);
	}
}

void ADummyButton::OnConfirm_Implementation(AActor* Actor)
{
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("BaseColor", FLinearColor::Green);
	}
}

void ADummyButton::OnCancel_Implementation(AActor* Actor)
{
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("BaseColor", FLinearColor::White);
	}
}

