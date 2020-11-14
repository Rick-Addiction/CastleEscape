// Copyright Henrique Rachti Assumpção 2020


#include "JigsawPuzzle.h"
#include <CastleEscape\Environment\DoorMovement.h>
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

}


// Called every frame
void UJigsawPuzzle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UJigsawPuzzle::SetCurrentPuzzlePiecePlaced(AActor* PuzzleSpace, AActor* PuzzlePiecePlaced) {
	for (int i = 0; i < JigsawPieceSpaces.Num(); i++)
		if (JigsawPieceSpaces[i].PuzzleSpace == PuzzleSpace) {
			JigsawPieceSpaces[i].CurrentPuzzlePiecePlaced = PuzzlePiecePlaced;
			break;
		}
}

void UJigsawPuzzle::SetPuzzlePieceRotation(AActor* PuzzleSpace, int PieceRotationIndex) {
	for (int i = 0; i < JigsawPieceSpaces.Num(); i++)
		if (JigsawPieceSpaces[i].PuzzleSpace == PuzzleSpace) {
			JigsawPieceSpaces[i].CurrentPuzzlePieceRotation = static_cast<EPuzzleRotation>(PieceRotationIndex);
		}
}

bool UJigsawPuzzle::CheckIfPuzzleSpaceIsAvailable(AActor* PuzzleSpaceToCheck)
{
	for (FJigsawPieceSpace p : JigsawPieceSpaces)
		if (p.PuzzleSpace == PuzzleSpaceToCheck) {
			return p.bAvailable;
		}

	return false;
}

void UJigsawPuzzle::SetPuzzleSpaceAvailability(AActor* PuzzleSpace, bool PuzzleSpaceAvailability)
{
	for (int i = 0; i < JigsawPieceSpaces.Num(); i++) {
		if (JigsawPieceSpaces[i].PuzzleSpace == PuzzleSpace) {
			JigsawPieceSpaces[i].bAvailable = PuzzleSpaceAvailability;
			break;
		}
	}
}

void UJigsawPuzzle::CheckIfItHasBeenSolved() {
	if (!CheckIfAllSpacesHasAPuzzle()) {
		GetOwner()->FindComponentByClass<UDoorMovement>()->SetDoorMovement(EDoorStatus::CLOSE);
		return;
	}

	for (int i = 0; i < JigsawPieceSpaces.Num(); i++) {
		if (JigsawPieceSpaces[i].PuzzlePieceExpected != JigsawPieceSpaces[i].CurrentPuzzlePiecePlaced) {
			GetOwner()->FindComponentByClass<UDoorMovement>()->SetDoorMovement(EDoorStatus::CLOSE);
			return;
		}

		if (JigsawPieceSpaces[i].PuzzlePieceRotationExpected != JigsawPieceSpaces[i].CurrentPuzzlePieceRotation) {
			GetOwner()->FindComponentByClass<UDoorMovement>()->SetDoorMovement(EDoorStatus::CLOSE);
			return;
		}
	}

	GetOwner()->FindComponentByClass<UDoorMovement>()->SetDoorMovement(EDoorStatus::OPEN);
}

bool UJigsawPuzzle::CheckIfAllSpacesHasAPuzzle() {
	for (int i = 0; i < JigsawPieceSpaces.Num(); i++)
		if (JigsawPieceSpaces[i].bAvailable == true) {
			return false;
		}

	return true;
}

