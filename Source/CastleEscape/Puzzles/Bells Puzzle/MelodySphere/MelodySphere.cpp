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

	

	if(WallWhereTheSphereIsPlaced && WallWhereTheSphereIsPlaced->FindComponentByClass<UBellsPuzzle>())
	BellsPuzzle = WallWhereTheSphereIsPlaced->FindComponentByClass<UBellsPuzzle>();

}

// Called every frame
void UMelodySphere::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(CurrentMelodySphereStatus == EInteractableObjectStats::PLAY)
	{
		if (GetCurrentValueHSV()<0.8)
		{
			ChangeSphereColor(1.0,DeltaTime);
		}
		else
		{
			CurrentMelodySphereStatus = EInteractableObjectStats::STOP;
		}		
	}
	else if (CurrentMelodySphereStatus == EInteractableObjectStats::STOP)
	{

		if (GetCurrentValueHSV()>0.0)
		{
			ChangeSphereColor(0.0,DeltaTime);
		}
		else
		{
			CurrentMelodySphereStatus = EInteractableObjectStats::NONE;
		}		
	}

}

void UMelodySphere::PlayMelody()
{
	if(BellsPuzzle)
	{
		BellsPuzzle->PlayBellsToSolve(this);
	}
}

void UMelodySphere::LightUpTheSphere()
{
	CurrentMelodySphereStatus = EInteractableObjectStats::PLAY;
}

void UMelodySphere::ChangeSphereColor(float ValueHSV,float DeltaTime)
{
	UMaterialInterface* MIMelodySphere = GetOwner()->FindComponentByClass<UStaticMeshComponent>()->GetMaterial(0);
	UMaterialInstanceDynamic* MatMelodySphereInstance = GetOwner()->FindComponentByClass<UStaticMeshComponent>()->CreateDynamicMaterialInstance(0, MIMelodySphere);
 
	if(MatMelodySphereInstance != nullptr)
	{
		FLinearColor CurrentMelodySphereColor= MatMelodySphereInstance->K2_GetVectorParameterValue("Gem_Depth_01_Color");
		//FLinearColor HSV  = CurrentMelodySphereColor.LinearRGBToHSV();		
		CurrentMelodySphereColor.R = FMath::FInterpTo(CurrentMelodySphereColor.R, ValueHSV , DeltaTime, SpeedToChangeColor);;
		//CurrentMelodySphereColor = HSV.HSVToLinearRGB();
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