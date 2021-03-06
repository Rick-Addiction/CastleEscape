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
	PrimaryComponentTick.SetTickFunctionEnable(false);
	CreateDynamicLiquidMaterial();
	SettingNextPipe();
	SettingValveThatControlsThePipe();
	
}

void UStraightPipe::SettingNextPipe()
{
	for (AActor* NextPipe : NextPipes)
	{
		if(NextPipe)
		{
			if(NextPipe->FindComponentByClass<UPipe>())
			{
				UPipe* NextPipeComponent = NextPipe->FindComponentByClass<UPipe>();
				NextPipeComponent->PreviousPipe = this;
			}
		}
	}
}

void UStraightPipe::SettingValveThatControlsThePipe()
{
	if(ValveThatControlsThisPipe)
	{
		if(ValveThatControlsThisPipe->FindComponentByClass<UPipeValve>())
		{
			UPipeValve* ValveComponent = ValveThatControlsThisPipe->FindComponentByClass<UPipeValve>();
			ValveComponent->SetPipeComponentThatValveControls(this);			
		}
	}
	
}


// Called every frame
void UStraightPipe::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(CurrentState ==SCHEDULED_TO_FLOW_WATER)
	{		//UE_LOG(LogTemp,Warning,TEXT("%s - %s : SCHEDULED_TO_FLOW_WATER"),*FDateTime::Now().ToString(), *GetOwner()->GetName());
		ManageScheduledFlowWater(DeltaTime);
	}
	if(CurrentState == FLOWING_WATER)
	{
		//UE_LOG(LogTemp,Warning,TEXT("%s - %s : FLOWING_WATER"),*FDateTime::Now().ToString(),*GetOwner()->GetName());
		ManageFlowWater(DeltaTime);
	}
	else if(CurrentState == SCHEDULED_TO_DRAIN_OUT_WATER)
	{
		//UE_LOG(LogTemp,Warning,TEXT("%s - %s : SCHEDULED_TO_DRAIN_OUT_WATER"),*FDateTime::Now().ToString(),*GetOwner()->GetName());
		ManageScheduledDrainOutWater(DeltaTime);		
	}
	else if(CurrentState == DRAINING_OUT_WATER)
	{
		//UE_LOG(LogTemp,Warning,TEXT("%s - %s : DRAINING_OUT_WATER"),*FDateTime::Now().ToString(),*GetOwner()->GetName());
		ManageDrainOutWater(DeltaTime);
	}
}

void UStraightPipe::ManageScheduledFlowWater(float DeltaTime)
{
	if(!IsPipeEmpty())
	{
		UE_LOG(LogTemp,Warning,TEXT("%s - %s : DrainOutWater"),*FDateTime::Now().ToString(),*GetOwner()->GetName());
		DrainOutWater(DeltaTime);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("%s - %s : ChangePipeToFlowingState"),*FDateTime::Now().ToString(),*GetOwner()->GetName());
		ChangePipeToFlowingState();
	}
}


void UStraightPipe::ManageFlowWater(float DeltaTime)
{	
	if(IsPipeFlowEnable())
	{
		if(!IsPipeFull())
		{
			FlowWater(DeltaTime);
		}
		else
		{
			CurrentState = FULL_OF_WATER;
			CheckAndFlowNextPipe();

		}
	}
}

void UStraightPipe::ManageScheduledDrainOutWater(float DeltaTime)
{
		if(!IsPipeFull())
		{
			FlowWater(DeltaTime);
		}
		else
		{
			if(PreviousPipe)
			{
				if(PreviousPipe->IsScheduledToDrainOutWater())
				{
					CurrentState = FULL_OF_WATER;
					PreviousPipe->SchedulePipeToDrainOutState();
				}
				else
				{
					ChangePipeToDrainOutState();					
				}
			}
			else
			{
				
				if(IsPipeDrainOutAble())
				{
					ChangePipeToDrainOutState();
				}
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
		CurrentState = EMPTY_OF_WATER;
		CheckAndDrainOutNextPipe();
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
	if(IsPipeDrainOutAble())
	{
		CurrentState = DRAINING_OUT_WATER;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("%s - %s : UNABLE to ChangePipeToDrainOutState"),*FDateTime::Now().ToString(),*GetOwner()->GetName());
		PrimaryComponentTick.SetTickFunctionEnable(false);
	}
}

void UStraightPipe::SchedulePipeToDrainOutState()
{
	if((PreviousPipe && PreviousPipe->IsPipeFull()) || !IsPipeEmpty())
	{
		PrimaryComponentTick.SetTickFunctionEnable(true);
	
		CurrentState = SCHEDULED_TO_DRAIN_OUT_WATER;
	}
}

void UStraightPipe::SchedulePipeToFlowWaterState()
{
	PrimaryComponentTick.SetTickFunctionEnable(true);
	if(!PreviousPipe || PreviousPipe->IsPipeFull())
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
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("%s - %s : UNABLE to ChangePipeToFlowingState"),*FDateTime::Now().ToString(),*GetOwner()->GetName());
		PrimaryComponentTick.SetTickFunctionEnable(false);
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

void UStraightPipe::CheckAndFlowNextPipe()
{
	for (AActor* NextPipe : NextPipes)
	{
		if(NextPipe != nullptr )
		{
			if(NextPipe->FindComponentByClass<UPipe>() != nullptr)
			{
				UE_LOG(LogTemp,Error,TEXT("SchedulePipeToFlowWaterState"));
				FTimerHandle handle;
				FTimerDelegate TimerDel;
				UPipe* NextPipeComponent = NextPipe->FindComponentByClass<UPipe>();
				GetWorld()->GetTimerManager().SetTimer(handle, NextPipeComponent, &UPipe::SchedulePipeToFlowWaterState,1,false);
			}
		}
	}
}

void UStraightPipe::CheckAndDrainOutNextPipe()
{
	for (AActor* NextPipe : NextPipes)
	{
		if(NextPipe != nullptr )
		{
			if(NextPipe->FindComponentByClass<UPipe>() != nullptr)
			{
				FTimerHandle handle;
				FTimerDelegate TimerDel;
				UPipe* NextPipeComponent = NextPipe->FindComponentByClass<UPipe>();
				GetWorld()->GetTimerManager().SetTimer(handle, NextPipeComponent, &UPipe::SchedulePipeToDrainOutState,1,false);
			}
		}
	}
}

bool UStraightPipe::IsScheduledToDrainOutWater()
{
	return CurrentState == SCHEDULED_TO_DRAIN_OUT_WATER;	
}

bool UStraightPipe::IsPipeFull()
{

	UStaticMeshComponent* LiquidSMComponent = GetLiquidStaticMeshComponent();
	const FVector CurrentLiquidSMScale = LiquidSMComponent->GetComponentScale();
	
	return CurrentLiquidSMScale.X>=1.1;
}

bool UStraightPipe::IsPipeEmpty()
{
	UStaticMeshComponent* LiquidSMComponent = GetLiquidStaticMeshComponent();
	const FVector CurrentLiquidSMScale = LiquidSMComponent->GetComponentScale();
	return CurrentLiquidSMScale.X<=0;
}

bool UStraightPipe::IsPipeFlowEnable()
{
	if(ValveThatControlsThisPipe && ValveThatControlsThisPipe->FindComponentByClass<UPipeValve>())
	{
		UPipeValve* ValveComponent = ValveThatControlsThisPipe->FindComponentByClass<UPipeValve>();

		if(ValveComponent->IsEnabled())
		{
			UE_LOG(LogTemp,Error,TEXT("VALVE IS ENABLE"));
		}
		else
		{
			UE_LOG(LogTemp,Error,TEXT("VALVE IS DISABLE"));
		}
		return ValveComponent->IsEnabled();
	}

	return true;
}

bool UStraightPipe::IsPipeDrainOutAble()
{
	if(NextPipes.Num()==0)
	{
		return true;
	}
	else if(NextPipes.Num()>1){
		for (AActor* NextPipe : NextPipes)
		{
			if(NextPipe->FindComponentByClass<UPipe>()->IsPipeFlowEnable()
				&& NextPipe->FindComponentByClass<UPipe>()->IsPipeDrainOutAble())
			{
				return true;
			}
		}
		return false;
	}
	else{		
		if(!NextPipes[0])
		{
			return true;
		}
		else
		{
			if(NextPipes[0]->FindComponentByClass<UPipe>()->IsPipeFlowEnable())
			{
				return NextPipes[0]->FindComponentByClass<UPipe>()->IsPipeDrainOutAble();				
			}
			else
			{
				return false;
			}
		}
	}
}
	
