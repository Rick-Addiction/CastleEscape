// Copyright Henrique Rachti Assumpção 2020


#include "StraightPipe.h"

// Sets default values for this component's properties
UStraightPipe::UStraightPipe()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStraightPipe::BeginPlay()
{
	Super::BeginPlay();

	CreateDynamicLiquidMaterial();
	
}


// Called every frame
void UStraightPipe::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(CurrentState == EPipeCurrentState::FLOWING_WATER)
	{
		if(!IsPipeFull())
		{
			FlowWater(DeltaTime);
		}
		else
		{
			CurrentState = EPipeCurrentState::FULL_OF_WATER;
			CheckAndStartNextPipe();
		}
	}
	else if(CurrentState == EPipeCurrentState::DRAINING_OUT_WATER)
	{
		if(!IsPipeEmpty())
		{
			DrainOutWater(DeltaTime);
		}
		else
		{
			CurrentState = EPipeCurrentState::EMPTY_OF_WATER;
		}
	}
}


void UStraightPipe::FlowWater(float DeltaTime)
{
	if(IsPipeFull()) return;
	
	UStaticMeshComponent* MaskComponent = GetLiquidStaticMeshComponent();
	if(MaskComponent != nullptr)
	{
		FVector CurrentMaskScale = MaskComponent->GetComponentScale();
		
			CurrentMaskScale.X+= FMath::Lerp<float>(0, 1 , 1 - FMath::Pow(WaterSpeed, DeltaTime));
			MaskComponent->SetWorldScale3D(CurrentMaskScale);
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("Material hasn't been created"));
	}
	
}

void UStraightPipe::ChangePipeToDrainOutMode()
{
	CurrentState = EPipeCurrentState::DRAINING_OUT_WATER;	
}

void UStraightPipe::ChangePipeToFlowingMode()
{
	USceneComponent* MaskComponent = GetLiquidSceneComponent();
	FVector CurrentMaskScale = MaskComponent->GetComponentScale();
	CurrentMaskScale.X=1;
	MaskComponent->SetWorldScale3D(CurrentMaskScale);

	UStaticMeshComponent* MaskComponent2 = GetLiquidStaticMeshComponent();
	FVector CurrentMaskScale2 = MaskComponent2->GetComponentScale();
	CurrentMaskScale2.X=0;
	MaskComponent2->SetWorldScale3D(CurrentMaskScale2);
	
	CurrentState = EPipeCurrentState::FLOWING_WATER;	
}


void UStraightPipe::DrainOutWater(float DeltaTime)
{
	if(IsPipeEmpty()){return;}
	else
	{
			
		USceneComponent* MaskComponent = GetLiquidSceneComponent();
		if(MaskComponent != nullptr)
		{
		
			FVector CurrentMaskScale = MaskComponent->GetComponentScale();
			CurrentMaskScale.X-= FMath::Lerp<float>(0, 1 , 1 - FMath::Pow(WaterSpeed, DeltaTime));
			MaskComponent->SetWorldScale3D(CurrentMaskScale);
		}
		else
		{
			UE_LOG(LogTemp,Error,TEXT("Material hasn't been created"));
		}
	}
	
}

void UStraightPipe::CheckAndStartNextPipe()
{
	if(NextPipe != nullptr )
	{
		if(NextPipe->FindComponentByClass<UPipe>() != nullptr)
		{
			FTimerHandle handle;
			FTimerDelegate TimerDel;
			UPipe* NextPipeComponent = NextPipe->FindComponentByClass<UPipe>();
			GetWorld()->GetTimerManager().SetTimer(handle, NextPipeComponent, &UPipe::ChangePipeToFlowingMode,1,false);
		}
	}
}


bool UStraightPipe::IsPipeFull()
{

	UStaticMeshComponent* LiquidSMComponent = GetLiquidStaticMeshComponent();
	const FVector CurrentLiquidSMScale = LiquidSMComponent->GetComponentScale();
	UE_LOG(LogTemp,Error,TEXT("TA CHEIO ? %s %f"), CurrentLiquidSMScale.X>=1 ? "SIM" : "NAO",CurrentLiquidSMScale.X );
	return CurrentLiquidSMScale.X>=1;
}

bool UStraightPipe::IsPipeEmpty()
{
	UStaticMeshComponent* LiquidSMComponent = GetLiquidStaticMeshComponent();
	const FVector CurrentLiquidSMScale = LiquidSMComponent->GetComponentScale();
	return CurrentLiquidSMScale.X<=0;
}





