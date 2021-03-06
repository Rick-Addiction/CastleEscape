// Copyright Henrique Rachti Assumpção 2020


#include "JigsawPiece.h"

#include "JigsawPuzzle.h"
#include "Components/AudioComponent.h"
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

	FRotator JigsawPieceRotation = GetOwner()->GetActorRotation();
	JigsawPieceRotation.Roll = GetJigsawPieceRotationRoll(this->CurrentJigsawPieceRotation);
	GetOwner()->SetActorRotation(JigsawPieceRotation);
	
}

int UJigsawPiece::GetJigsawPieceRotationRoll(EJigsawPieceRotationRoll e) {
	switch (e) {
	case TOP: return 0;
	case LEFT: return 90;
	case BOTTOM: return 180;
	case RIGHT: return 270;    	
	}	
	return 0;
}

void UJigsawPiece::SetPlaceJigsawPieceAudioComponent(USoundBase* PlaceJigsawPieceSound)
{
	PlaceJigsawPieceAudioComponent = NewObject<UAudioComponent>(GetOwner());
	PlaceJigsawPieceAudioComponent->SetSound(PlaceJigsawPieceSound);	
}

// Called every frame
void UJigsawPiece::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UJigsawPiece::PlacePuzzleObjectInPuzzleSpace() {
	FRotator PieceRotationToPut = PuzzleSpace->GetActorRotation();
	PieceRotationToPut.Roll = GetCurrentRotationRoll();
	GetOwner()->SetActorRotation(PieceRotationToPut);
	GetOwner()->SetActorLocation(PuzzleSpace->GetActorLocation());
		

	static_cast<UJigsawPuzzle*>(Puzzle)->SetPuzzleSpaceAvailability(PuzzleSpace, false);
	static_cast<UJigsawPuzzle*>(Puzzle)->SetCurrentPuzzlePiecePlaced(PuzzleSpace, this);
	static_cast<UJigsawPuzzle*>(Puzzle)->CheckIfItHasBeenSolved();

	LastPuzzleSpaceOccupied = PuzzleSpace;
	GetOwner()->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);

	if (PlaceJigsawPieceAudioComponent) {
		PlaceJigsawPieceAudioComponent->Play();
	}
}

void UJigsawPiece::RemovePuzzleObjectFromPuzzleSpace() {
	if (LastPuzzleSpaceOccupied != nullptr) {
		static_cast<UJigsawPuzzle*>(Puzzle)->SetPuzzleSpaceAvailability(LastPuzzleSpaceOccupied, true);
		static_cast<UJigsawPuzzle*>(Puzzle)->CheckIfItHasBeenSolved();
		LastPuzzleSpaceOccupied = nullptr;
	}

	GetOwner()->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(true);

	if (PlaceJigsawPieceAudioComponent) {
		PlaceJigsawPieceAudioComponent->Play();
	}
}

float UJigsawPiece::GetNextRotationRoll()
{
	CurrentJigsawPieceRotation = static_cast<EJigsawPieceRotationRoll>((CurrentJigsawPieceRotation + 1) % (RIGHT + 1));
	return GetJigsawPieceRotationRoll(CurrentJigsawPieceRotation);
}	

float UJigsawPiece::GetCurrentRotationRoll() const{
	return GetJigsawPieceRotationRoll(CurrentJigsawPieceRotation);
}