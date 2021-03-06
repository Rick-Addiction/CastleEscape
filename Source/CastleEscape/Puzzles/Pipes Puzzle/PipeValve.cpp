// Copyright Henrique Rachti Assumpção 2020


#include "PipeValve.h"

// Sets default values for this component's properties
UPipeValve::UPipeValve()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPipeValve::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.SetTickFunctionEnable(false);
}

// Called every frame
void UPipeValve::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(PipeValveAction == EInteractableObjectAction::PLAYING)
	{
		TurnValve(DeltaTime);
	}
	else
	{
		PrimaryComponentTick.SetTickFunctionEnable(false);
	}
	
}

void UPipeValve::Play()
{
	if(PipeComponentsThatValveControlsTheFlow.Num()==0){return;}
	
	if(PipeValveAction == EInteractableObjectAction::STOPPING)
	{
		PipeValveAction = EInteractableObjectAction::PLAYING;
		ChangePipesValveState();
		PrimaryComponentTick.SetTickFunctionEnable(true);		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("There isn't a Pipe Component or an Pipe Actor controlled by the Valve %s"),*GetOwner()->GetName())
	}
}

void UPipeValve::TurnValve(float DeltaTime)
{
	FRotator CurrentPipeValveRotation = GetOwner()->GetActorRotation();
	

	if(PipeValveState == ENABLED)
	{
		if(CurrentPipeValveRotation.Roll < 45)
		{
			CurrentPipeValveRotation.Roll+= FMath::Lerp<float>(0, 45 , 1 - FMath::Pow(ValveSpeed, DeltaTime));
			GetOwner()->SetActorRotation(CurrentPipeValveRotation);		
		}
		else
		{
			PipeValveAction = EInteractableObjectAction::STOPPING;
		}
	}
	else if(PipeValveState == DISABLED)
	{
		if (CurrentPipeValveRotation.Roll > 0)
		{
			CurrentPipeValveRotation.Roll-= FMath::Lerp<float>(0, 45 , 1 - FMath::Pow(ValveSpeed, DeltaTime));
			GetOwner()->SetActorRotation(CurrentPipeValveRotation);
		}
		else
		{
			PipeValveAction = EInteractableObjectAction::STOPPING;
		}
	}
}

void UPipeValve::AddPipeComponentThatValveControls(UPipe* PipeComponentThatValveControls)
{
	this->PipeComponentsThatValveControlsTheFlow.Add(PipeComponentThatValveControls);	
}

void UPipeValve::ChangePipesValveState()
{
	if(PipeComponentsThatValveControlsTheFlow.Num()==0){return;}
	
	PipeValveState = static_cast<EPipeValveState>((PipeValveState + 1) % (ENABLED +1));
	
	for(UPipe* PipeComponent : PipeComponentsThatValveControlsTheFlow)
	{
		
	
		FTimerHandle handle;
		FTimerDelegate TimerDel;
		if(PipeValveState == ENABLED)
		{
			GetWorld()->GetTimerManager().SetTimer(handle, PipeComponent, &UPipe::SchedulePipeToFlowWaterState,DelayToChangePipeState,false);
		}
		else if(PipeValveState == DISABLED)
		{
			GetWorld()->GetTimerManager().SetTimer(handle, PipeComponent, &UPipe::SchedulePipeToDrainOutState,DelayToChangePipeState,false);
		}
	}
}

bool UPipeValve::IsEnabled() const
{
	return PipeValveState == ENABLED;
}
