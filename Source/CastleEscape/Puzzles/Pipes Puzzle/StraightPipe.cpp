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
	SettingNextPipes();
	SettingValveThatControlsThePipe();
	HideWater();
}

void UStraightPipe::SettingNextPipes()
{
	for (FSourcesOfWater SourceOfWater : SourcesOfWater)
	{
		if(SourceOfWater.Pipe && SourceOfWater.Pipe->FindComponentByClass<UPipe>())
		{			
				UPipe* PreviousPipeComponent = SourceOfWater.Pipe->FindComponentByClass<UPipe>();
				PreviousPipeComponent->NextPipes.Add(this);

		}
	}
}

void UStraightPipe::SettingValveThatControlsThePipe()
{
	for(FSourcesOfWater SourceOfWater : SourcesOfWater){
		if(SourceOfWater.ValveThatEnableTheFlow)
		{
			if(SourceOfWater.ValveThatEnableTheFlow->FindComponentByClass<UPipeValve>())
			{
				UPipeValve* ValveComponent = SourceOfWater.ValveThatEnableTheFlow->FindComponentByClass<UPipeValve>();
				ValveComponent->AddPipeComponentThatValveControls(this);			
			}
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
	if(IsPipeAbleToFlowWater())
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
			if(SourcesOfWater.Num() > 0)
			{
				bool bPreviousPipeScheduledToDrainOutWater = false;
				for(FSourcesOfWater SourceOfWater : SourcesOfWater)
				{
					if((SourceOfWater.Pipe && SourceOfWater.Pipe->FindComponentByClass<UPipe>())
					&& SourceOfWater.Pipe->FindComponentByClass<UPipe>()->IsScheduledToDrainOutWater())
					{
						CurrentState = FULL_OF_WATER;
						bPreviousPipeScheduledToDrainOutWater=true;
						SourceOfWater.Pipe->FindComponentByClass<UPipe>()->SchedulePipeToDrainOutState();
					}
				}
				if(!bPreviousPipeScheduledToDrainOutWater)
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
		HideWater();
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
	UE_LOG(LogTemp,Error,TEXT("%s - %s : SchedulePipeToDrainOutState"),*FDateTime::Now().ToString(),*GetOwner()->GetName());
	for(FSourcesOfWater SourceOfWater : SourcesOfWater)
	{
		if(SourceOfWater.Pipe && SourceOfWater.Pipe->FindComponentByClass<UPipe>())
		{
			if(SourceOfWater.Pipe->FindComponentByClass<UPipe>()->IsPipeFull())
			{
				if(SourceOfWater.ValveThatEnableTheFlow &&
                    SourceOfWater.ValveThatEnableTheFlow->FindComponentByClass<UPipeValve>()
                    && SourceOfWater.ValveThatEnableTheFlow->FindComponentByClass<UPipeValve>()->IsEnabled())
				{
					return;
				}
			}
		}
		else
		{
			if(SourceOfWater.ValveThatEnableTheFlow &&
                    SourceOfWater.ValveThatEnableTheFlow->FindComponentByClass<UPipeValve>()
                    && SourceOfWater.ValveThatEnableTheFlow->FindComponentByClass<UPipeValve>()->IsEnabled())
			{
				return;
			}
		}
	}

	PrimaryComponentTick.SetTickFunctionEnable(true);	
	CurrentState = SCHEDULED_TO_DRAIN_OUT_WATER;	
}

void UStraightPipe::SchedulePipeToFlowWaterState()
{
	UE_LOG(LogTemp,Error,TEXT("%s - %s : SchedulePipeToFlowWaterState"),*FDateTime::Now().ToString(),*GetOwner()->GetName());
	PrimaryComponentTick.SetTickFunctionEnable(true);

	if(SourcesOfWater.Num() >0 )
	{
		for(FSourcesOfWater SourceOfWater : SourcesOfWater)
		{
			if(SourceOfWater.Pipe && SourceOfWater.Pipe->FindComponentByClass<UPipe>())
			{
				if(!SourceOfWater.Pipe->FindComponentByClass<UPipe>()->IsPipeFull()){continue;}

				UPipe* PreviousPipeComponent = SourceOfWater.Pipe->FindComponentByClass<UPipe>();
			
				if(this->IsPipeEmpty() && PreviousPipeComponent->IsPipeFull())
				{		
					CurrentState = SCHEDULED_TO_FLOW_WATER;
					return;
				}
			}
			else
			{
				if(this->IsPipeEmpty())
				{		
					CurrentState = SCHEDULED_TO_FLOW_WATER;
					return;
				}
			}
		}
	}
	else
	{
		CurrentState = SCHEDULED_TO_FLOW_WATER;
		return;
	}
}

void UStraightPipe::ChangePipeToFlowingState()
{
	if(IsPipeAbleToFlowWater())
	{		
		USceneComponent* MaskComponent = GetLiquidSceneComponent();
		FVector CurrentMaskScale = MaskComponent->GetComponentScale();
		CurrentMaskScale.X=1;
		MaskComponent->SetWorldScale3D(CurrentMaskScale);

		UStaticMeshComponent* MaskComponent2 = GetLiquidStaticMeshComponent();
		FVector CurrentMaskScale2 = MaskComponent2->GetComponentScale();
		CurrentMaskScale2.X=0;
		MaskComponent2->SetWorldScale3D(CurrentMaskScale2);
		
		ExposeWater();
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
	for (UPipe* NextPipe : NextPipes)
	{
		if(NextPipe != nullptr )
		{
			if(NextPipe != nullptr)
			{
				UE_LOG(LogTemp,Error,TEXT("SchedulePipeToFlowWaterState"));
				FTimerHandle handle;
				FTimerDelegate TimerDel;
				GetWorld()->GetTimerManager().SetTimer(handle, NextPipe, &UPipe::SchedulePipeToFlowWaterState,1,false);
			}
		}
	}
}

void UStraightPipe::CheckAndDrainOutNextPipe()
{
	for (UPipe* NextPipe : NextPipes)
	{
		if(NextPipe != nullptr )
		{
			if(NextPipe != nullptr)
			{
				FTimerHandle handle;
				FTimerDelegate TimerDel;
				GetWorld()->GetTimerManager().SetTimer(handle, NextPipe, &UPipe::SchedulePipeToDrainOutState,1,false);
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

bool UStraightPipe::IsPipeAbleToFlowWater()
{	if(SourcesOfWater.Num()>0)
	{
		for(FSourcesOfWater SourceOfWater : SourcesOfWater)
		{
			if(SourceOfWater.Pipe && SourceOfWater.Pipe->FindComponentByClass<UPipe>())
			{
				if(SourceOfWater.Pipe->FindComponentByClass<UPipe>()->IsPipeFull())
				{
					if(!SourceOfWater.ValveThatEnableTheFlow ||
                        !SourceOfWater.ValveThatEnableTheFlow->FindComponentByClass<UPipeValve>()
                        || (SourceOfWater.ValveThatEnableTheFlow->FindComponentByClass<UPipeValve>())->IsEnabled())
					{
						return true;
					}
				}				
			}
			else
			{
				if(!SourceOfWater.ValveThatEnableTheFlow ||
                        !SourceOfWater.ValveThatEnableTheFlow->FindComponentByClass<UPipeValve>()
                        || (SourceOfWater.ValveThatEnableTheFlow->FindComponentByClass<UPipeValve>())->IsEnabled())
				{
					return true;
				}
			}			
		}
	return false;
	}

	return true;
}

bool UStraightPipe::IsOneOfTheValvesThatControlsThePipeEnable()
{
	bool bValveEnabledNotFound=false;

	return true;
}


bool UStraightPipe::IsPipeDrainOutAble()
{
	if(NextPipes.Num()==0)
	{
		return true;
	}
	else if(NextPipes.Num()>1){
		for (UPipe* NextPipe : NextPipes)
		{
			if(NextPipe)
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
			if(NextPipes[0]->IsPipeAbleToFlowWater())
			{
				return NextPipes[0]->IsPipeDrainOutAble();				
			}
			else
			{
				return false;
			}
		}
	}
}
	
void UStraightPipe::HideWater()
{
	UE_LOG(LogTemp,Warning,TEXT("%s - %s : HideWater"),*FDateTime::Now().ToString(),*GetOwner()->GetName());
	//UStaticMeshComponent* LiquidSMComponent = GetLiquidStaticMeshComponent();
	//LiquidSMComponent->SetVisibility(false,true);
}

void UStraightPipe::ExposeWater()
{
	UE_LOG(LogTemp,Warning,TEXT("%s - %s : ExposeWater"),*FDateTime::Now().ToString(),*GetOwner()->GetName());
	//UStaticMeshComponent* LiquidSMComponent = GetLiquidStaticMeshComponent();
	//LiquidSMComponent->SetVisibility(true,true);
}