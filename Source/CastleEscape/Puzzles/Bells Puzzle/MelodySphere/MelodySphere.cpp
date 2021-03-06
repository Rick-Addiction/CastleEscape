// Copyright Henrique Rachti Assumpção 2020


#include "MelodySphere.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UMelodySphere::UMelodySphere()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UMelodySphere::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UMelodySphere::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(CurrentMelodySphereStatus == EInteractableObjectAction::PLAYING)
	{
		if (GetCurrentValueHSV()<0.8)
		{
			ChangeSphereColor(1.0,DeltaTime);
		}
		else
		{
			CurrentMelodySphereStatus = EInteractableObjectAction::STOPPING;
		}		
	}
	else if (CurrentMelodySphereStatus == EInteractableObjectAction::STOPPING)
	{

		if (GetCurrentValueHSV()>0.0)
		{
			ChangeSphereColor(0.0,DeltaTime);
		}
		else
		{
			CurrentMelodySphereStatus = EInteractableObjectAction::NONE;
		}		
	}

}

void UMelodySphere::SetBellsPuzzle(UBellsPuzzle* BellsPuzzle)
{
	this->BellsPuzzle=BellsPuzzle;
}

void UMelodySphere::Play()
{
	if(BellsPuzzle)
	{
		BellsPuzzle->PlayBellsToSolve();
	}
}

void UMelodySphere::LightUpTheSphere()
{
	CurrentMelodySphereStatus = EInteractableObjectAction::PLAYING;
}

void UMelodySphere::ChangeSphereColor(float ValueHSV,float DeltaTime)
{
	UMaterialInterface* MIMelodySphere = GetOwner()->FindComponentByClass<UStaticMeshComponent>()->GetMaterial(0);
	UMaterialInstanceDynamic* MatMelodySphereInstance = GetOwner()->FindComponentByClass<UStaticMeshComponent>()->CreateDynamicMaterialInstance(0, MIMelodySphere);
 
	if(MatMelodySphereInstance != nullptr)
	{
		FLinearColor CurrentMelodySphereColor= MatMelodySphereInstance->K2_GetVectorParameterValue("Gem_Depth_01_Color");
		CurrentMelodySphereColor.R = FMath::FInterpTo(CurrentMelodySphereColor.R, ValueHSV , DeltaTime, SpeedToChangeColor);;
		MatMelodySphereInstance->SetVectorParameterValue("Gem_Depth_01_Color", CurrentMelodySphereColor);
	}
}

float UMelodySphere::GetCurrentValueHSV()
{
	UMaterialInterface* MIMelodySphere = GetOwner()->FindComponentByClass<UStaticMeshComponent>()->GetMaterial(0);
	UMaterialInstanceDynamic* MatMelodySphereInstance = GetOwner()->FindComponentByClass<UStaticMeshComponent>()->CreateDynamicMaterialInstance(0, MIMelodySphere);
 
	if(MatMelodySphereInstance != nullptr)
	{
		FLinearColor CurrentMelodySphereColor= MatMelodySphereInstance->K2_GetVectorParameterValue("Gem_Depth_01_Color");
		FLinearColor HSV  = CurrentMelodySphereColor.LinearRGBToHSV();		
		return HSV.B;		
	}

	return 0;
}