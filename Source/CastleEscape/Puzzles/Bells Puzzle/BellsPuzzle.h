// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"

#include "CastleEscape/Puzzles/Puzzle.h"

#include "BellsPuzzle.generated.h"


class UBell;
class UMelodySphere;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UBellsPuzzle : public UPuzzle
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBellsPuzzle();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFirstPuzzle=false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExpectedZWallLocationWhenPuzzleSolved=380.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WallMovementSpeed = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBellsPuzzle* NextBellsPuzzle=nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* MelodySpheceActor=nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> SequenceOfBellsToSolve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> BellsAvailableToPlay;
	
	void PlayBellsToSolve();

	void CheckIfTheBellHasBeenPlayedInTheRightSequence(UBell* BellPlayed);

	virtual void CheckIfItHasBeenSolved() override;
	
protected:
	UPROPERTY()
	TArray<UAudioComponent*> BellsAudioComponents;

	UPROPERTY()
	TArray<UBell*> BellsPlayedInTheRightSequence;

	UPROPERTY()
	UMelodySphere* MelodySphere = nullptr;
	
	UPROPERTY()
	bool bIsPuzzleSolved=false;

	UPROPERTY()
	float CurrentZWallLocation;

	void StoreBellsToSolveAudioComponents();

	void UpdateBellsPuzzleInTheBells();

	void TurnUpActor(float DeltaTime, AActor* ActorToTurnUp);

	UFUNCTION()
	void PlayOneOfTheBellsToSolve(int BellIndex);

};
