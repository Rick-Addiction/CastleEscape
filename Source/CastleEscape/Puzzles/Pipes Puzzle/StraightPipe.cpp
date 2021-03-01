// Copyright Henrique Rachti Assumpção 2020


#include "StraightPipe.h"

#include "PipeValve.h"

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
	SettingNextPipe();
	SettingValveThatControlsThePipe();
	
}

void UStraightPipe::SettingNextPipe()
{
	if(NextPipe)
	{
		if(NextPipe->FindComponentByClass<UPipe>())
		{
			UPipe* NextPipeComponent = NextPipe->FindComponentByClass<UPipe>();
			NextPipeComponent->PreviousPipe = this->GetOwner();
		}
	}
}

void UStraightPipe::SettingValveThatControlsThePipe()
{
	if(ValveThatControlsThePipe)
	{
		if(ValveThatControlsThePipe->FindComponentByClass<UPipeValve>())
		{
			UPipeValve* ValveComponent = ValveThatControlsThePipe->FindComponentByClass<UPipeValve>();
			ValveComponent->SetPipeComponentThatValveControls(this);			
		}
	}
	
}


// Called every frame
void UStraightPipe::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(CurrentState == FLOWING_WATER
		|| CurrentState == SCHEDULED_TO_DRAIN_OUT_WATER)
	{
		ManageFlowWater(DeltaTime);
	}
	else if(CurrentState == DRAINING_OUT_WATER
	|| CurrentState == SCHEDULED_TO_FLOW_WATER)
	{
		ManageDrainOutWater(DeltaTime);
	}
}

void UStraightPipe::ManageFlowWater(float DeltaTime)
{
	if(!IsPipeFull())
	{
		FlowWater(DeltaTime);
	}
	else
	{
		if(CurrentState == FLOWING_WATER)
		{
			CurrentState = FULL_OF_WATER;
			CheckAndStartNextPipe();
		}
		else if(CurrentState == SCHEDULED_TO_DRAIN_OUT_WATER)
		{
			ChangePipeToDrainOutState();
		}
	}
}

void UStraightPipe::ManageDrainOutWater(float DeltaTime)
{
	if(!IsPipeEmpty())
	{
		DrainOutWater(DeltaTime);
	}
	else
	{
		if(CurrentState == DRAINING_OUT_WATER)
		{
			CurrentState = EMPTY_OF_WATER;
		}
		else if(CurrentState == SCHEDULED_TO_FLOW_WATER)
		{
			ChangePipeToFlowingState();
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
		
			CurrentMaskScale.X+= FMath::Lerp<float>(0, 1.1 , 1 - FMath::Pow(WaterSpeed, DeltaTime));
			MaskComponent->SetWorldScale3D(CurrentMaskScale);
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("Material hasn't been created"));
	}
	
}

void UStraightPipe::ChangePipeToDrainOutState()
{
	CurrentState = DRAINING_OUT_WATER;
}

void UStraightPipe::SchedulePipeToDrainOutState()
{
	CurrentState = SCHEDULED_TO_DRAIN_OUT_WATER;	
}

void UStraightPipe::SchedulePipeToFlowWaterState()
{
	if(!PreviousPipe || PreviousPipe->FindComponentByClass<UPipe>()->IsPipeFull())
	{
		CurrentState = SCHEDULED_TO_FLOW_WATER;
	}
}

void UStraightPipe::ChangePipeToFlowingState()
{
	if(IsPipeFlowEnable())
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
			CurrentMaskScale.X-= FMath::Lerp<float>(0, 1.1 , 1 - FMath::Pow(WaterSpeed, DeltaTime));
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
			GetWorld()->GetTimerManager().SetTimer(handle, NextPipeComponent, &UPipe::SchedulePipeToFlowWaterState,1,false);
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

bool UStraightPipe::IsPipeFlowEnable()
{
	if(ValveThatControlsThePipe && ValveThatControlsThePipe->FindComponentByClass<UPipeValve>())
	{
		UPipeValve* ValveComponent = ValveThatControlsThePipe->FindComponentByClass<UPipeValve>();
		return ValveComponent->IsEnabled();
	}

	return true;
}





