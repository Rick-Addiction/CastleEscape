// Copyright Henrique Rachti Assumpção 2020


#include "Pipe.h"

USceneComponent* UPipe::GetLiquidSceneComponent()
{
	USceneComponent* DefaultSceneComponent = GetOwner()->FindComponentByClass<USceneComponent>();
	TArray<USceneComponent*> ArrayUSceneComponents;
	DefaultSceneComponent->GetChildrenComponents(false, ArrayUSceneComponents);

	if(ArrayUSceneComponents.Num() > 0)
	{
		TArray<USceneComponent*>::ElementType* LiquidSceneComponent = ArrayUSceneComponents.FindByPredicate([&](USceneComponent* InItem)
          {
              return InItem->GetName() == "Liquid";
          });
		
		if(LiquidSceneComponent)
		{
			return *LiquidSceneComponent;
		}
		else
		{
			return nullptr;		
		}
	}
	else
	{
		return nullptr;		
	}
}

UStaticMeshComponent* UPipe::GetLiquidStaticMeshComponent()
{	
		USceneComponent* LiquidSceneComponent = GetLiquidSceneComponent();
	
		if(!LiquidSceneComponent) return nullptr;
	
		return Cast<UStaticMeshComponent>(LiquidSceneComponent->GetChildComponent(0));

}

void UPipe::CreateDynamicLiquidMaterial()
{
	UStaticMeshComponent* LiquidComponent = GetLiquidStaticMeshComponent();
	if(LiquidComponent)
	{
		UMaterialInterface* MILiquidMaterial = LiquidComponent->GetMaterial(0);
		UMaterialInstanceDynamic* MILiquidDynamicMaterial = LiquidComponent->CreateDynamicMaterialInstance(0, MILiquidMaterial);
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("Liquid Component hasn't found"));
	}
}


