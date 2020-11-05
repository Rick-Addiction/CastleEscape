// Copyright Henrique Rachti Assumpção 2020

#include "PuzzlePiece.h"
#include "GameFramework/Actor.h"
#include "UObject/Object.h"
#include "Engine/World.h"
#include "Math/Vector.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Controller.h"
#include <CastleEscape\Grabber.h>

// Sets default values for this component's properties
UPuzzlePiece::UPuzzlePiece()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UPuzzlePiece::BeginPlay()
{
	Super::BeginPlay();	

	if (ActorThatContainsMainPuzzleComponent == nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("%s don't have a DoorThatOpensWhenPuzzleComplete attached on it"), *GetOwner()->GetName());
	}
	else {
		if (ActorThatContainsMainPuzzleComponent->FindComponentByClass<UPuzzle>() == nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("%s don't have Puzzle component on it"), *ActorThatContainsMainPuzzleComponent->GetName());
		}
		else {
			Puzzle = ActorThatContainsMainPuzzleComponent->FindComponentByClass<UPuzzle>();
			SettingAudioComponent();
		}
	}	
}

void UPuzzlePiece::SettingAudioComponent() {
	PlacePuzzleAudioComponent = NewObject<UAudioComponent>(GetOwner());
	PlacePuzzleAudioComponent->SetSound(Puzzle->GetPlacePuzzleSound());

	RemovePuzzleAudioComponent = NewObject<UAudioComponent>(GetOwner());
	RemovePuzzleAudioComponent->SetSound(Puzzle->GetRemovePuzzleSound());
}


// Called every frame
void UPuzzlePiece::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Puzzle) { return; }
	
	if (bGrabbedByPlayer) {
		if (PuzzleSpace && Puzzle->CheckIfPuzzleSpaceIsAvailable(PuzzleSpace) && !HasBeenPlaced()) {
			if (PuzzleSpace->IsOverlappingActor(GetOwner())) {
				PlacePieceInPuzzleSpace();
			}			
		}
		else if(!PuzzleSpace && !HasBeenRemoved()){
			RemovePieceFromPuzzleSpace();
		}
	}
}



void UPuzzlePiece::RemovePieceFromPuzzleSpace() {
	if (LastPuzzleSpaceOccupied != nullptr) {
		Puzzle->SetPuzzleSpaceAvailability(LastPuzzleSpaceOccupied, true);
		Puzzle->CheckIfItHasBeenSolved();
		LastPuzzleSpaceOccupied = nullptr;
	}

	GetOwner()->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(true);

	if (RemovePuzzleAudioComponent) {
		RemovePuzzleAudioComponent->Play();
	}
}


void UPuzzlePiece::SetGrabbedByPlayer(bool isGrabbed) {
	bGrabbedByPlayer = isGrabbed;
}

void UPuzzlePiece::SetPuzzleSpace(AActor* PuzzleSpaceFound) {
	PuzzleSpace = (ATriggerVolume*)PuzzleSpaceFound;
}

bool UPuzzlePiece::HasBeenRemoved() {
	return GetOwner()->FindComponentByClass<UPrimitiveComponent>()->IsSimulatingPhysics() == true;
}

bool UPuzzlePiece::HasBeenPlaced() {
	return GetOwner()->FindComponentByClass<UPrimitiveComponent>()->IsSimulatingPhysics() == false;
}

