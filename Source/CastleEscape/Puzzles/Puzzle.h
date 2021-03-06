// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Puzzle.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UPuzzle : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzle();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetCurrentPuzzlePiecePlaced(ATriggerVolume* PuzzleSpace, UActorComponent* PuzzlePiecePlaced) { check(0 && "You must override this"); }

	virtual void SetPuzzleSpaceAvailability(ATriggerVolume* PuzzleSpace, bool PuzzleSpaceAvailability) { check(0 && "You must override this"); }

	virtual void CheckIfItHasBeenSolved() { check(0 && "You must override this"); }

	virtual bool IsPuzzleSpaceAvailable(ATriggerVolume* PuzzleSpaceToCheck) { check(0 && "You must override this"); return false;}

	virtual bool IsAllSpacesUnavailable() { check(0 && "You must override this"); return false; }

	virtual bool IsAllSpacesAvailable() { check(0 && "You must override this"); return false; }	
		
};
