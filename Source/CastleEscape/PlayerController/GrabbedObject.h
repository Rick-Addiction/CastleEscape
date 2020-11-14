// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "UObject/Object.h"
#include "Components/AudioComponent.h"
#include <CastleEscape\Puzzles\Puzzle.h>
#include "GrabbedObject.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UGrabbedObject : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabbedObject();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetGrabbedByPlayer(bool isGrabbed);

	void SetPuzzleSpace(AActor* PuzzleSpaceFound);
	
		
protected:
	virtual void PlacePieceInPuzzleSpace() { check(0 && "You must override this"); }
	virtual void RemovePieceFromPuzzleSpace() { check(0 && "You must override this"); }
	void SettingAudioComponent();
	bool HasBeenRemoved();
	bool HasBeenPlaced();

	UPROPERTY(EditAnywhere)
	AActor* ActorThatContainsMainPuzzleComponent = nullptr;

	UAudioComponent* PlacePuzzleAudioComponent = nullptr;

	UAudioComponent* RemovePuzzleAudioComponent = nullptr;

	ATriggerVolume* PuzzleSpace = nullptr;

	UPuzzle* Puzzle = nullptr;

	bool bGrabbedByPlayer = false;

	ATriggerVolume* LastPuzzleSpaceOccupied = nullptr;

	

};
