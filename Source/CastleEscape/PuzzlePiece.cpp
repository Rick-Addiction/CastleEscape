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

	// ...
}


// Called when the game starts
void UPuzzlePiece::BeginPlay()
{
	Super::BeginPlay();

	if (PuzzleSpace == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("%s don't have a PuzzleSpace attached on it"), *GetOwner()->GetName());
	}

	if (DoorThatOpensWhenPuzzleComplete == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("%s don't have a DoorThatOpensWhenPuzzleComplete attached on it"), *GetOwner()->GetName());
	}
	else {
		if (DoorThatOpensWhenPuzzleComplete->FindComponentByClass<UJigsawPuzzle>() == nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("%s don't have Puzzle component on it"), *DoorThatOpensWhenPuzzleComplete->GetName());
		}
		else {
			Puzzle = DoorThatOpensWhenPuzzleComplete->FindComponentByClass<UJigsawPuzzle>();
		}
	}
	
}


// Called every frame
void UPuzzlePiece::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Puzzle) { return; }
	
	if (bGrabbedByPlayer) {
		if (PuzzleSpace && Puzzle->CheckIfPuzzleSpaceIsAvailable(PuzzleSpace)) {
			if (PuzzleSpace->IsOverlappingActor(GetOwner())) {
					PutPieceInPuzzleSpace();
			}			
		}
		else if(!PuzzleSpace){
			
			RemovePieceFromPuzzleSpace();
		}

	}
}

void UPuzzlePiece::PutPieceInPuzzleSpace() {
	GetOwner()->SetActorRotation(PuzzleSpace->GetActorRotation());
	GetOwner()->SetActorLocation(PuzzleSpace->GetActorLocation());

	UE_LOG(LogTemp, Warning, TEXT("SPACE FALSE"))
	Puzzle->SetPuzzleSpaceAvailability(PuzzleSpace,false);
	LastPuzzleSpaceOccupied = PuzzleSpace;
	GetOwner()->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);
}

void UPuzzlePiece::RemovePieceFromPuzzleSpace() {
	if (LastPuzzleSpaceOccupied != nullptr) {
		UE_LOG(LogTemp, Error, TEXT("SPACE TRUE"))
		Puzzle->SetPuzzleSpaceAvailability(LastPuzzleSpaceOccupied, true);
		LastPuzzleSpaceOccupied = nullptr;
	}

	GetOwner()->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(true);
}

void UPuzzlePiece::SetGrabbedByPlayer(bool isGrabbed) {
	bGrabbedByPlayer = isGrabbed;
}

void UPuzzlePiece::SetPuzzleSpace(AActor* PuzzleSpaceFound) {
	PuzzleSpace = (ATriggerVolume*)PuzzleSpaceFound;
}

