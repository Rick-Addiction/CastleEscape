// Copyright Henrique Rachti Assumpção 2020

#include "GrabbedObject.h"
#include "GameFramework/Actor.h"
#include "UObject/Object.h"
#include "Math/Vector.h"
#include "Components/PrimitiveComponent.h"

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

}




// Called every frame
void UGrabbedObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPrimitiveComponent* GrabbedObjectPrimitiveComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	const FVector CurrentObjectVelocity = GetOwner()->GetVelocity();
	if(CurrentObjectVelocity.Z > 50.f){
		GetOwner()->FindComponentByClass<UStaticMeshComponent>()->SetLinearDamping(10.f);

		//UE_LOG(LogTemp,Error,TEXT("SUBINDO"))
		//UE_LOG(LogTemp,Warning,TEXT("Actor: %s | Velocity: %s"),*GetOwner()->GetName(),*CurrentObjectVelocity.ToString())
	}
	else
	{
		GetOwner()->FindComponentByClass<UStaticMeshComponent>()->SetLinearDamping(0.01f);
			
		//UE_LOG(LogTemp,Error,TEXT("DESCENDO"));
		//UE_LOG(LogTemp,Warning,TEXT("Actor: %s | Velocity: %s"),*GetOwner()->GetName(),*CurrentObjectVelocity.ToString())
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

void UGrabbedObject::SetGrabbedByPlayer(bool IsGrabbed) {
	bGrabbedByPlayer = IsGrabbed;
}

void UGrabbedObject::SetPuzzleSpace(ATriggerVolume* PuzzleSpaceFound) {
	PuzzleSpace = PuzzleSpaceFound;
}

void UGrabbedObject::SetPuzzle(UPuzzle* PuzzleToSet) {
	Puzzle = PuzzleToSet;
}

bool UGrabbedObject::IsThePuzzlePlaced() const {
	return GetOwner()->FindComponentByClass<UPrimitiveComponent>()->IsSimulatingPhysics() == false;
}

bool UGrabbedObject::ShouldThePuzzleObjectBePlaced() const {
	return PuzzleSpace && Puzzle && Puzzle->IsPuzzleSpaceAvailable(PuzzleSpace)
	&& PuzzleSpace->IsOverlappingActor(GetOwner())
	&& GetOwner()->FindComponentByClass<UPrimitiveComponent>()->IsSimulatingPhysics() == true;
}

bool UGrabbedObject::ShouldThePuzzleObjectBeRemoved() const {
	return !PuzzleSpace
    && GetOwner()->FindComponentByClass<UPrimitiveComponent>()->IsSimulatingPhysics() == false;
}

