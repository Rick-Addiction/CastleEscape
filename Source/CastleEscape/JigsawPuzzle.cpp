// Copyright Henrique Rachti Assumpção 2020


#include "JigsawPuzzle.h"
#include <CastleEscape\DoorMovement.h>
#include "GameFramework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UJigsawPuzzle::UJigsawPuzzle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UJigsawPuzzle::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UJigsawPuzzle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UJigsawPuzzle::CheckIfPuzzleSpaceIsAvailable(AActor* PuzzleSpaceToCheck)
{
	for (FPuzzleSpace p : PuzzleSpaceArray)
		if (p.PuzzleSpace == PuzzleSpaceToCheck) {
			return p.bAvailable;
		}

	return false;
}

void UJigsawPuzzle::SetPuzzleSpaceAvailability(AActor* PuzzleSpace, bool PuzzleSpaceAvailability)
{
	for (int i = 0; i < PuzzleSpaceArray.Num(); i++) {
			if (PuzzleSpaceArray[i].PuzzleSpace == PuzzleSpace) {
				PuzzleSpaceArray[i].bAvailable = PuzzleSpaceAvailability;
			}
	}
}

void UJigsawPuzzle::SetPuzzlePieceRotation(AActor* PuzzleSpace, int PieceRotationIndex) {

	for (int i = 0; i < PuzzleSpaceArray.Num(); i++)
		if (PuzzleSpaceArray[i].PuzzleSpace == PuzzleSpace) {
			PuzzleSpaceArray[i].CurrentPuzzlePieceRotation = static_cast<EPuzzleRotation>(PieceRotationIndex);
			}

}

void UJigsawPuzzle::SetCurrentPuzzlePiecePlaced(AActor* PuzzleSpace, AActor* PuzzlePiecePlaced) {

	for (int i = 0; i < PuzzleSpaceArray.Num(); i++)
		if (PuzzleSpaceArray[i].PuzzleSpace == PuzzleSpace) {
			PuzzleSpaceArray[i].CurrentPuzzlePiecePlaced = PuzzlePiecePlaced;
		}
}


void UJigsawPuzzle::CheckIfItHasBeenSolved() {

	if (!CheckIfAllSpacesHasAPuzzle()) { 
		GetOwner()->FindComponentByClass<UDoorMovement>()->SetDoorMovement(EDoorStatus::CLOSE);
		return; 
	}

	for (int i = 0; i < PuzzleSpaceArray.Num(); i++) {
		if (PuzzleSpaceArray[i].PuzzlePieceExpected != PuzzleSpaceArray[i].CurrentPuzzlePiecePlaced) {
			GetOwner()->FindComponentByClass<UDoorMovement>()->SetDoorMovement(EDoorStatus::CLOSE);
			return;
		}

		if (PuzzleSpaceArray[i].PuzzlePieceRotationExpected != PuzzleSpaceArray[i].CurrentPuzzlePieceRotation) {
			GetOwner()->FindComponentByClass<UDoorMovement>()->SetDoorMovement(EDoorStatus::CLOSE);
			return;
		}
	}

	GetOwner()->FindComponentByClass<UDoorMovement>()->SetDoorMovement(EDoorStatus::OPEN);
	
}

bool UJigsawPuzzle::CheckIfAllSpacesHasAPuzzle() {

	for (int i = 0; i < PuzzleSpaceArray.Num(); i++)
		if (PuzzleSpaceArray[i].bAvailable == true) {
			return false;
		}

	return true;
}

