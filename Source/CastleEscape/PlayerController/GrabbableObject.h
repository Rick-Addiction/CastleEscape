// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "CastleEscape/Puzzles/Puzzle.h"
#include "GrabbableObject.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UGrabbableObject : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabbableObject();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetGrabbedByPlayer(bool IsGrabbed);

	void SetPuzzleSpace(ATriggerVolume* PuzzleSpaceFound);

	void SetPuzzle(UPuzzle* PuzzleToSet);
	
		
protected:
	virtual void PlacePuzzleObjectInPuzzleSpace() { check(0 && "You must override this"); }
	virtual void RemovePuzzleObjectFromPuzzleSpace() { check(0 && "You must override this"); }
	
	bool ShouldThePuzzleObjectBePlaced() const;
	bool ShouldThePuzzleObjectBeRemoved() const;
	bool IsThePuzzlePlaced() const;

	UPROPERTY()
	ATriggerVolume* PuzzleSpace = nullptr;

	UPROPERTY()
	UPuzzle* Puzzle = nullptr;

	UPROPERTY()
	bool bGrabbedByPlayer = false;

	UPROPERTY()
	ATriggerVolume* LastPuzzleSpaceOccupied = nullptr;

	

};
