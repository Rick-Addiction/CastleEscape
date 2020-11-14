// Copyright Henrique Rachti Assumpção 2020

#include "GrabbedObject.h"
#include "GameFramework/Actor.h"
#include "UObject/Object.h"
#include "Engine/World.h"
#include "Math/Vector.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Controller.h"

// Sets default values for this component's properties
UGrabbedObject::UGrabbedObject()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UGrabbedObject::BeginPlay()
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

void UGrabbedObject::SettingAudioComponent() {
	PlacePuzzleAudioComponent = NewObject<UAudioComponent>(GetOwner());
	PlacePuzzleAudioComponent->SetSound(Puzzle->GetPlacePuzzleSound());

	RemovePuzzleAudioComponent = NewObject<UAudioComponent>(GetOwner());
	RemovePuzzleAudioComponent->SetSound(Puzzle->GetRemovePuzzleSound());
}


// Called every frame
void UGrabbedObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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

void UGrabbedObject::SetGrabbedByPlayer(bool isGrabbed) {
	bGrabbedByPlayer = isGrabbed;
}

void UGrabbedObject::SetPuzzleSpace(AActor* PuzzleSpaceFound) {
	PuzzleSpace = (ATriggerVolume*)PuzzleSpaceFound;
}

bool UGrabbedObject::HasBeenRemoved() {
	return GetOwner()->FindComponentByClass<UPrimitiveComponent>()->IsSimulatingPhysics() == true;
}

bool UGrabbedObject::HasBeenPlaced() {
	return GetOwner()->FindComponentByClass<UPrimitiveComponent>()->IsSimulatingPhysics() == false;
}

