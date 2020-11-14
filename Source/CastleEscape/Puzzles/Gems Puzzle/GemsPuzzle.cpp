// Copyright Henrique Rachti Assumpção 2020


#include "GemsPuzzle.h"

// Sets default values for this component's properties
UGemsPuzzle::UGemsPuzzle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGemsPuzzle::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGemsPuzzle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGemsPuzzle::SetCurrentPuzzlePiecePlaced(AActor* GemSpace, AActor* GemPlaced)
{
	for (int i = 0; i < GemSpaces.Num(); i++)
		if (GemSpaces[i].PuzzleSpace == GemPlaced) {
			
			
			
			GemSpaces[i].CurrentGemPlaced = GemPlaced;
			break;
		}	
}

bool UGemsPuzzle::CheckIfPuzzleSpaceIsAvailable(AActor* GemSpaceToCheck)
{
	for (FGemSpace p : GemSpaces)
		if (p.PuzzleSpace == GemSpaceToCheck) {
			return p.bAvailable;
		}

	return false;
}

void UGemsPuzzle::SetPuzzleSpaceAvailability(AActor* GemSpace, bool GemSpaceAvailability)
{
	for (int i = 0; i < GemSpaces.Num(); i++) {
		if (GemSpaces[i].PuzzleSpace == GemSpace) {
			GemSpaces[i].bAvailable = GemSpaceAvailability;
			break;
		}
	}

	
}

void UGemsPuzzle::CheckIfItHasBeenSolved()
{


	
}

bool UGemsPuzzle::CheckIfAllSpacesHasAPuzzle()
{
	for (int i = 0; i < GemSpaces.Num(); i++)
		if (GemSpaces[i].bAvailable == true) {
			return false;
		}

	return true;
}



