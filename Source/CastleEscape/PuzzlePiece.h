// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "UObject/Object.h"
#include "Components/AudioComponent.h"
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

	void SetGrabbedByPlayer(bool isGrabbed);

	void SetPuzzleSpace(AActor* PuzzleSpaceFound);

	float GetNextRotationRoll();

	float GetCurrentRotationRoll();
		
private:
	void SettingAudioComponent();
	void PlacePieceInPuzzleSpace();
	void RemovePieceFromPuzzleSpace();
	bool HasBeenRemoved();
	bool HasBeenPlaced();

	UPROPERTY(EditAnywhere)
	AActor* DoorThatOpensWhenPuzzleComplete = nullptr;

	UAudioComponent* PlacePuzzleAudioComponent = nullptr;

	UAudioComponent* RemovePuzzleAudioComponent = nullptr;

	ATriggerVolume* PuzzleSpace = nullptr;

	UJigsawPuzzle* Puzzle = nullptr;

	bool bGrabbedByPlayer = false;

	ATriggerVolume* LastPuzzleSpaceOccupied = nullptr;

	TArray<float> PossibleRotation = { 0.f,90.f,180.f,270.f };
	int CurrentPossibleRotationIndex =0;
	int LastPossibleRotationIndex = 3;

	

};
