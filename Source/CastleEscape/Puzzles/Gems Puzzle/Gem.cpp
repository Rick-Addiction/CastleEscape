// Copyright Henrique Rachti Assumpção 2020


#include "Gem.h"

#include "GemsPuzzle.h"

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

	((UGemsPuzzle*)Puzzle)->SetPuzzleSpaceAvailability(PuzzleSpace, false);
	((UGemsPuzzle*)Puzzle)->SetCurrentPuzzlePiecePlaced(PuzzleSpace, GetOwner());
	//TODO Puzzle->CheckIfItHasBeenSolved();
	
	
	LastPuzzleSpaceOccupied = PuzzleSpace;
	GetOwner()->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);

	if (PlacePuzzleAudioComponent) {
		PlacePuzzleAudioComponent->Play();
	}
}

void UGem::RemovePieceFromPuzzleSpace() {
	if (LastPuzzleSpaceOccupied != nullptr) {
		((UGemsPuzzle*)Puzzle)->SetPuzzleSpaceAvailability(LastPuzzleSpaceOccupied, true);
		((UGemsPuzzle*)Puzzle)->SetCurrentPuzzlePiecePlaced(LastPuzzleSpaceOccupied, nullptr);

		//TODO Puzzle->CheckIfItHasBeenSolved();
		LastPuzzleSpaceOccupied = nullptr;
	}

	GetOwner()->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(true);

	if (RemovePuzzleAudioComponent) {
		RemovePuzzleAudioComponent->Play();
	}
}

FLinearColor UGem::GetGemColor()
{
	UMaterialInstanceDynamic* MIGem = UMaterialInstanceDynamic::Create(
                    GetOwner()->FindComponentByClass<UPrimitiveComponent>()->GetMaterial(0),
                    this);

	FLinearColor GemColor;
	MIGem->GetVectorParameterValue(FName(TEXT("Gem_Depth_01_Color")),OUT GemColor, false);

	return GemColor;	
}

