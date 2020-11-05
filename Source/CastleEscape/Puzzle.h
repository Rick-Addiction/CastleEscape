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


	UPROPERTY(EditAnywhere)
		USoundBase* PlacePuzzleSound = nullptr;
	UPROPERTY(EditAnywhere)
		USoundBase* RemovePuzzleSound = nullptr;

	virtual void SetCurrentPuzzlePiecePlaced(AActor* PuzzleSpace, AActor* PuzzlePiecePlaced) { check(0 && "You must override this"); }

	virtual bool CheckIfPuzzleSpaceIsAvailable(AActor* PuzzleSpaceToCheck) { check(0 && "You must override this"); return 0;}

	virtual void SetPuzzleSpaceAvailability(AActor* PuzzleSpace, bool PuzzleSpaceAvailability) { check(0 && "You must override this"); }

	virtual void CheckIfItHasBeenSolved() { check(0 && "You must override this"); }

	virtual bool CheckIfAllSpacesHasAPuzzle() { check(0 && "You must override this"); return 0; }

	USoundBase* GetPlacePuzzleSound();
	USoundBase* GetRemovePuzzleSound();
		
};
