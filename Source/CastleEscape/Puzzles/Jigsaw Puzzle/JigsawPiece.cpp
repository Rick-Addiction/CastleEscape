// Copyright Henrique Rachti Assumpção 2020


#include "JigsawPiece.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/TriggerVolume.h"

// Sets default values for this component's properties
UJigsawPiece::UJigsawPiece()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UJigsawPiece::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UJigsawPiece::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UJigsawPiece::PlacePieceInPuzzleSpace() {
	FRotator PieceRotationToPut = PuzzleSpace->GetActorRotation();
	PieceRotationToPut.Roll = GetCurrentRotationRoll();
	GetOwner()->SetActorRotation(PieceRotationToPut);
	GetOwner()->SetActorLocation(PuzzleSpace->GetActorLocation());
		

	((UJigsawPuzzle*)Puzzle)->SetPuzzleSpaceAvailability(PuzzleSpace, false);
	((UJigsawPuzzle*)Puzzle)->SetPuzzlePieceRotation(PuzzleSpace, CurrentPossibleRotationIndex);
	((UJigsawPuzzle*)Puzzle)->SetCurrentPuzzlePiecePlaced(PuzzleSpace, GetOwner());
	((UJigsawPuzzle*)Puzzle)->CheckIfItHasBeenSolved();

	LastPuzzleSpaceOccupied = PuzzleSpace;
	GetOwner()->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);

	if (PlacePuzzleAudioComponent) {
		PlacePuzzleAudioComponent->Play();
	}
}

void UJigsawPiece::RemovePieceFromPuzzleSpace() {
	if (LastPuzzleSpaceOccupied != nullptr) {
		((UJigsawPuzzle*)Puzzle)->SetPuzzleSpaceAvailability(LastPuzzleSpaceOccupied, true);
		((UJigsawPuzzle*)Puzzle)->CheckIfItHasBeenSolved();
		LastPuzzleSpaceOccupied = nullptr;
	}

	GetOwner()->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(true);

	if (RemovePuzzleAudioComponent) {
		RemovePuzzleAudioComponent->Play();
	}
}

float UJigsawPiece::GetNextRotationRoll() {

	if (CurrentPossibleRotationIndex != LastPossibleRotationIndex) {
		return PossibleRotation[++CurrentPossibleRotationIndex];
	}
	else {
		CurrentPossibleRotationIndex = 0;
		return PossibleRotation[CurrentPossibleRotationIndex];
	}
}

float UJigsawPiece::GetCurrentRotationRoll() {
	return PossibleRotation[CurrentPossibleRotationIndex];
}