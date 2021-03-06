// Copyright Henrique Rachti Assumpção 2020

#include "GrabbableObject.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UGrabbableObject::UGrabbableObject()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UGrabbableObject::BeginPlay()
{
	Super::BeginPlay();	

}

// Called every frame
void UGrabbableObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPrimitiveComponent* GrabbedObjectPrimitiveComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	if(GrabbedObjectPrimitiveComponent)
	{
		const FVector CurrentObjectVelocity = GetOwner()->GetVelocity();
		if(CurrentObjectVelocity.Z > 50.f){
			GetOwner()->FindComponentByClass<UStaticMeshComponent>()->SetLinearDamping(10.f);

		}
		else
		{
			GetOwner()->FindComponentByClass<UStaticMeshComponent>()->SetLinearDamping(0.01f);
			
		}
	}
	if (bGrabbedByPlayer) {
		if (ShouldThePuzzleObjectBePlaced()){
			PlacePuzzleObjectInPuzzleSpace();			
		}
		else if(ShouldThePuzzleObjectBeRemoved()){
			RemovePuzzleObjectFromPuzzleSpace();
		}
	}
}

void UGrabbableObject::SetGrabbedByPlayer(bool IsGrabbed) {
	bGrabbedByPlayer = IsGrabbed;
}

void UGrabbableObject::SetPuzzleSpace(ATriggerVolume* PuzzleSpaceFound) {
	PuzzleSpace = PuzzleSpaceFound;
}

void UGrabbableObject::SetPuzzle(UPuzzle* PuzzleToSet) {
	Puzzle = PuzzleToSet;
}

bool UGrabbableObject::IsThePuzzlePlaced() const {
	return GetOwner()->FindComponentByClass<UPrimitiveComponent>()->IsSimulatingPhysics() == false;
}

bool UGrabbableObject::ShouldThePuzzleObjectBePlaced() const {
	return PuzzleSpace && Puzzle && Puzzle->IsPuzzleSpaceAvailable(PuzzleSpace)
	&& PuzzleSpace->IsOverlappingActor(GetOwner())
	&& GetOwner()->FindComponentByClass<UPrimitiveComponent>()->IsSimulatingPhysics() == true;
}

bool UGrabbableObject::ShouldThePuzzleObjectBeRemoved() const {
	return !PuzzleSpace
    && GetOwner()->FindComponentByClass<UPrimitiveComponent>()->IsSimulatingPhysics() == false;
}

