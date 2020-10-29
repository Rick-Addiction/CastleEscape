// Copyright Henrique Rachti Assumpção 2020

#include "GameFramework/Actor.h"
#include "UObject/Object.h"
#include "Engine/World.h"
#include "Math/Vector.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Controller.h"
#include <CastleEscape\Grabber.h>
#include "PuzzlePiece.h"


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
	
}


// Called every frame
void UPuzzlePiece::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (bGrabbedByPlayer) {
		if (PuzzleSpace) {
			if (PuzzleSpace->IsOverlappingActor(GetOwner())) {
					PutPieceInPuzzleSpace();
			}			
		}
		else {
			RemovePieceFromPuzzleSpace();
		}

	}
}

void UPuzzlePiece::PutPieceInPuzzleSpace() {
	GetOwner()->SetActorRotation(PuzzleSpace->GetActorRotation());
	GetOwner()->SetActorLocation(PuzzleSpace->GetActorLocation());
	GetOwner()->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);
}

void UPuzzlePiece::RemovePieceFromPuzzleSpace() {
	GetOwner()->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(true);
}

void UPuzzlePiece::SetGrabbedByPlayer(bool isGrabbed) {
	bGrabbedByPlayer = isGrabbed;
}

void UPuzzlePiece::SetPuzzleSpace(AActor* PuzzleSpaceFound) {
	PuzzleSpace = (ATriggerVolume*)PuzzleSpaceFound;
}

