// Copyright Henrique Rachti Assumpção 2020


#include "BellsPuzzle.h"

#include "Bell/Bell.h"
#include "Components/AudioComponent.h"
#include "CastleEscape/Puzzles/Bells Puzzle/MelodySphere/MelodySphere.h"

// Sets default values for this component's properties
UBellsPuzzle::UBellsPuzzle()
{
	
}

// Called when the game starts
void UBellsPuzzle::BeginPlay()
{
	Super::BeginPlay();

	PrimaryComponentTick.SetTickFunctionEnable(false);

	StoreBellsToSolveAudioComponents();
	if(IsFirstPuzzle)
	{
		UpdateBellsPuzzleInTheBells();
	}

	CurrentZWallLocation=GetOwner()->GetActorLocation().Z;

	if(MelodySpheceActor && MelodySpheceActor->FindComponentByClass<UMelodySphere>()){
		MelodySphere = MelodySpheceActor->FindComponentByClass<UMelodySphere>();
		MelodySphere->SetBellsPuzzle(this);
	}
	
}

void UBellsPuzzle::UpdateBellsPuzzleInTheBells()
{
	for(int i=0; i < BellsAvailableToPlay.Num(); i++)
	{
		BellsAvailableToPlay[i]->FindComponentByClass<UBell>()->AddBellsPuzzle(this);
	}	
}

void UBellsPuzzle::StoreBellsToSolveAudioComponents()
{
	for (int i = 0; i < SequenceOfBellsToSolve.Num(); i++)
	{
		UAudioComponent* BellAudioComponent = SequenceOfBellsToSolve[i]->FindComponentByClass<UBell>()->GetBellAudioComponent();
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
	UE_LOG(LogTemp,Warning,TEXT("TICK"));
	if(bIsPuzzleSolved)
	{
		if(GetOwner()->FindComponentByClass<USceneComponent>()->Mobility != EComponentMobility::Movable)
			GetOwner()->FindComponentByClass<USceneComponent>()->SetMobility(EComponentMobility::Movable);
			
        
		if (CurrentZWallLocation > ExpectedZWallLocationWhenPuzzleSolved-2.0) {
			GetOwner()->FindComponentByClass<USceneComponent>()->SetMobility(EComponentMobility::Static);

			if(MelodySphere)
			{
				MelodySpheceActor->FindComponentByClass<USceneComponent>()->SetMobility(EComponentMobility::Static);
				MelodySphere->DestroyComponent();				
			}
			DestroyComponent();
			UE_LOG(LogTemp,Warning,TEXT("DESTROY"));
		}
		else {
			TurnUpActor(DeltaTime,GetOwner());
			TurnUpActor(DeltaTime,MelodySpheceActor);
		}
	}
	
}

void UBellsPuzzle::PlayBellsToSolve()
{
	if(!MelodySphere){return;}		

	for (int i = 0; i < BellsAudioComponents.Num(); i++)
	{
		UE_LOG(LogTemp,Warning,TEXT("Playinggg %d"),i);
		FTimerHandle handle;
		FTimerDelegate TimerDel;
		if(i==0)
		{
			if(this)
			{
				PlayOneOfTheBellsToSolve(i);
			}
		}
		else
		{
			if(this)
			{
				TimerDel.BindUFunction(this, FName("PlayOneOfTheBellsToSolve"), i,MelodySphere);
				GetWorld()->GetTimerManager().SetTimer(handle, TimerDel,i*1,0);
			}
		}
	}	
}

void UBellsPuzzle::PlayOneOfTheBellsToSolve(int BellIndex)
{
	if(!MelodySphere){return;}
	
	if(MelodySpheceActor && MelodySpheceActor->FindComponentByClass<UMelodySphere>())
	{
		MelodySphere = MelodySpheceActor->FindComponentByClass<UMelodySphere>();
	}
	else
	{
		return;		
	}
	
		UE_LOG(LogTemp,Warning,TEXT("Playing %d"),BellIndex);
		BellsAudioComponents[BellIndex]->Play();

		MelodySphere->LightUpTheSphere();	
}

void UBellsPuzzle::CheckIfTheBellHasBeenPlayedInTheRightSequence(UBell* BellPlayed)
{
	if(!BellPlayed){return;}
	
	int CurrentBellIndex = 0;
	if(BellsPlayedInTheRightSequence.Num()>0)
	{
		CurrentBellIndex = BellsPlayedInTheRightSequence.Num();
	}

	if(SequenceOfBellsToSolve[CurrentBellIndex]->FindComponentByClass<UBell>()==BellPlayed)
	{
		BellsPlayedInTheRightSequence.Add(BellPlayed);
		CheckIfItHasBeenSolved();
	}
	else
	{
		BellsPlayedInTheRightSequence.Empty();
	}
}

void UBellsPuzzle::CheckIfItHasBeenSolved()
{
	if(BellsPlayedInTheRightSequence.Num()==SequenceOfBellsToSolve.Num())
	{
		UE_LOG(LogTemp,Warning,TEXT("SOLVED"));
		bIsPuzzleSolved=true;
		PrimaryComponentTick.SetTickFunctionEnable(true);
		
		if(NextBellsPuzzle)
		{
			NextBellsPuzzle->UpdateBellsPuzzleInTheBells();
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("UNSOLVED"));		
	}
}

void UBellsPuzzle::TurnUpActor(float DeltaTime,AActor* ActorToTurnUp)
{
	if(!ActorToTurnUp){return;}
	
	CurrentZWallLocation = FMath::FInterpTo(CurrentZWallLocation, ExpectedZWallLocationWhenPuzzleSolved , DeltaTime, WallMovementSpeed);
	FVector CurrentLocation = ActorToTurnUp->GetActorLocation();
	CurrentLocation.Z=CurrentZWallLocation;
	ActorToTurnUp->SetActorLocation(CurrentLocation);
}