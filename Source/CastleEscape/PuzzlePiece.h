// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "UObject/Object.h"
#include <CastleEscape\JigsawPuzzle.h>
#include "PuzzlePiece.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UPuzzlePiece : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzlePiece();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PutPieceInPuzzleSpace();

	void RemovePieceFromPuzzleSpace();

	void SetGrabbedByPlayer(bool isGrabbed);

	void SetPuzzleSpace(AActor* PuzzleSpaceFound);
		
private:

	UPROPERTY(EditAnywhere)
	AActor* DoorThatOpensWhenPuzzleComplete = nullptr;

	ATriggerVolume* PuzzleSpace = nullptr;

	UJigsawPuzzle* Puzzle = nullptr;

	bool bGrabbedByPlayer = false;

	ATriggerVolume* LastPuzzleSpaceOccupied = nullptr;

	

};
