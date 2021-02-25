// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Pipe.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UPipe : public UActorComponent
{
	GENERATED_BODY()


	protected:
	virtual void BeginPlay(){Super::BeginPlay();}
	virtual void CreateDynamicLiquidMaterial(){ check(0 && "You must override this"); };
	UStaticMeshComponent* GetLiquidComponent();
	UStaticMeshComponent* GetMaskComponent();
	
	public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){ Super::TickComponent(DeltaTime, TickType, ThisTickFunction);};
	virtual void FlowWater(float DeltaTime){ check(0 && "You must override this"); };
};