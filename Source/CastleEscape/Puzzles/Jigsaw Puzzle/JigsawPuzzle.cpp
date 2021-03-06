// Copyright Henrique Rachti Assumpção 2020


#include "JigsawPuzzle.h"
#include "CastleEscape/Environment/DoorMovement.h"
#include "CastleEscape/Puzzles/Jigsaw Puzzle/JigsawPiece.h"

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

	SettingJigsawPieceSpaces();
	SettingJigsawPieces();

}

void UJigsawPuzzle::SettingJigsawPieceSpaces() {	
	for(int i=0; i < JigsawPieceSpaces.Num(); i++)
	{
		FJigsawPieceSpaceState JigsawPieceSpaceState;
		JigsawPieceSpaceState.JigsawPieceSpace=JigsawPieceSpaces[i];
		JigsawPieceSpacesStates.Add(JigsawPieceSpaceState);
	}
}

void UJigsawPuzzle::SettingJigsawPieces() {	
	for(int i=0; i < JigsawPieces.Num(); i++)
	{
		UJigsawPiece* JigsawPieceComponent = JigsawPieces[i]->FindComponentByClass<UJigsawPiece>();
	
		if(JigsawPieceComponent)
		{
			if(PlaceJigsawPieceSound)
			{
				JigsawPieceComponent->SetPlaceJigsawPieceAudioComponent(PlaceJigsawPieceSound);
			}
		
			JigsawPieceComponent->SetPuzzle(this);			
		}
	}
}


// Called every frame
void UJigsawPuzzle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UJigsawPuzzle::SetCurrentPuzzlePiecePlaced(ATriggerVolume* JigsawPieceSpace, UActorComponent* JigsawPiecePlaced) {
	for (int i = 0; i < JigsawPieceSpaces.Num(); i++)
		if (JigsawPieceSpacesStates[i].JigsawPieceSpace == JigsawPieceSpace) {
			JigsawPieceSpacesStates[i].CurrentJigsawPiecePlaced = static_cast<UJigsawPiece*>(JigsawPiecePlaced);
			break;
		}
}

bool UJigsawPuzzle::IsPuzzleSpaceAvailable(ATriggerVolume* JigsawPieceSpaceToCheck)
{
	for (FJigsawPieceSpaceState p : JigsawPieceSpacesStates)
		if (p.JigsawPieceSpace == JigsawPieceSpaceToCheck) {
			return p.bAvailable;
		}

	return false;
}

void UJigsawPuzzle::SetPuzzleSpaceAvailability(ATriggerVolume* PuzzleSpace, const bool bPuzzleSpaceAvailability)
{
	for (int i = 0; i < JigsawPieceSpaces.Num(); i++) {
		if (JigsawPieceSpacesStates[i].JigsawPieceSpace == PuzzleSpace) {
			JigsawPieceSpacesStates[i].bAvailable = bPuzzleSpaceAvailability;
			break;
		}
	}
}

void UJigsawPuzzle::CheckIfItHasBeenSolved() {
	if (!IsAllSpacesUnavailable()) {
		GetOwner()->FindComponentByClass<UDoorMovement>()->SetDoorMovement(EDoorStats::CLOSE);
		return;
	}

	for (int i = 0; i < JigsawPieceSpaces.Num(); i++) {
		if (JigsawPieceSpacesStates[i].CurrentJigsawPiecePlaced->JigsawPieceSpaceExpected!=JigsawPieceSpacesStates[i].JigsawPieceSpace) {
			GetOwner()->FindComponentByClass<UDoorMovement>()->SetDoorMovement(EDoorStats::CLOSE);
			return;
		}

		if (JigsawPieceSpacesStates[i].CurrentJigsawPiecePlaced->GetCurrentRotationRoll() != 0) {
			GetOwner()->FindComponentByClass<UDoorMovement>()->SetDoorMovement(EDoorStats::CLOSE);
			return;
		}
	}

	GetOwner()->FindComponentByClass<UDoorMovement>()->SetDoorMovement(EDoorStats::OPEN);
}

bool UJigsawPuzzle::IsAllSpacesUnavailable() {
	for (int i = 0; i < JigsawPieceSpaces.Num(); i++)
		if (JigsawPieceSpacesStates[i].bAvailable == true) {
			return false;
		}
	return true;
}