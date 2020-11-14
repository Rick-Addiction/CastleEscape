// Copyright Henrique Rachti Assumpção 2020


#include "Gem.h"

// Sets default values for this component's properties
UGem::UGem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts	
void UGem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UGem::PlacePieceInPuzzleSpace() {
	GetOwner()->SetActorLocation(PuzzleSpace->GetActorLocation());
	FRotator NewGrabbedObjectRotation = PuzzleSpace->GetActorRotation();
	NewGrabbedObjectRotation.Roll -= 90;
	GetOwner()->SetActorRotation(NewGrabbedObjectRotation);

	Puzzle->SetPuzzleSpaceAvailability(PuzzleSpace, false);
	Puzzle->SetCurrentPuzzlePiecePlaced(PuzzleSpace, GetOwner());
	//Puzzle->CheckIfItHasBeenSolved();

	LastPuzzleSpaceOccupied = PuzzleSpace;
	GetOwner()->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);

	if (PlacePuzzleAudioComponent) {
		PlacePuzzleAudioComponent->Play();
	}
}

void UGem::RemovePieceFromPuzzleSpace() {
	if (LastPuzzleSpaceOccupied != nullptr) {
		Puzzle->SetPuzzleSpaceAvailability(LastPuzzleSpaceOccupied, true);
		//Puzzle->CheckIfItHasBeenSolved();
		LastPuzzleSpaceOccupied = nullptr;
	}

	GetOwner()->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(true);

	if (RemovePuzzleAudioComponent) {
		RemovePuzzleAudioComponent->Play();
	}
}

