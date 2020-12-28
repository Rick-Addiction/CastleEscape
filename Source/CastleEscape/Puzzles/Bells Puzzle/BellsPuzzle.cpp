// Copyright Henrique Rachti Assumpção 2020


#include "BellsPuzzle.h"

#include "Bell/Bell.h"
#include "Components/AudioComponent.h"
#include "CastleEscape/Puzzles/Bells Puzzle/MelodySphere/MelodySphere.h"

// Sets default values for this component's properties
UBellsPuzzle::UBellsPuzzle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UBellsPuzzle::BeginPlay()
{
	Super::BeginPlay();

	StoreBellsToSolveAudioComponents();
	
}

void UBellsPuzzle::StoreBellsToSolveAudioComponents()
{
	for (int i = 0; i < BellsToSolve.Num(); i++)
	{
		UAudioComponent* BellAudioComponent = BellsToSolve[i]->FindComponentByClass<UBell>()->GetBellAudioComponent();
		if(BellAudioComponent)
		{
			BellsAudioComponents.Add(BellAudioComponent);
		}		
	}	
}

// Called every frame
void UBellsPuzzle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBellsPuzzle::PlayBellsToSolve(UMelodySphere* MelodySphere)
{
	for (int i = 0; i < BellsAudioComponents.Num(); i++)
	{
		UE_LOG(LogTemp,Warning,TEXT("Playinggg %d"),i);
		FTimerHandle handle;
		FTimerDelegate TimerDel;
		if(i==0)
		{
			PlayOneOfTheBellsToSolve(i,MelodySphere);
		}
		else
		{
			TimerDel.BindUFunction(this, FName("PlayOneOfTheBellsToSolve"), i,MelodySphere);
			GetWorld()->GetTimerManager().SetTimer(handle, TimerDel,i*1,0);
		}
	}	
}

void UBellsPuzzle::PlayOneOfTheBellsToSolve(int BellIndex,UMelodySphere* MelodySphere)
{
	UE_LOG(LogTemp,Warning,TEXT("Playing %d"),BellIndex);
	BellsAudioComponents[BellIndex]->Play();

	if(MelodySphere)
	MelodySphere->LightUpTheSphere();
}