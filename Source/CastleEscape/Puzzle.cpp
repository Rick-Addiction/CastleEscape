// Copyright Henrique Rachti Assumpção 2020


#include "Puzzle.h"

// Sets default values for this component's properties
UPuzzle::UPuzzle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPuzzle::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPuzzle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

bool UPuzzle::CheckIfPuzzleSpaceIsAvailable(AActor* PuzzleSpaceToCheck)
{
	for (FPuzzleSpace p : PuzzleSpaceArray)
		if (p.PuzzleSpace == PuzzleSpaceToCheck) {
			return p.bAvailable;
		}

	UE_LOG(LogTemp,Error, TEXT("%s isn't in the PuzzleSpaceArray"),*PuzzleSpaceToCheck->GetName())

	return false;
}

void UPuzzle::SetPuzzleSpaceAvailability(AActor* PuzzleSpace, bool PuzzleSpaceAvailability)
{
	int numOfPuzzleSpaces = sizeof(PuzzleSpaceArray) / sizeof(PuzzleSpaceArray[0]);

	for (int i = 0; i < numOfPuzzleSpaces;i++)
		if (PuzzleSpaceArray[i].PuzzleSpace == PuzzleSpace) {
			PuzzleSpaceArray[i].bAvailable = PuzzleSpaceAvailability;			
		}	
}



