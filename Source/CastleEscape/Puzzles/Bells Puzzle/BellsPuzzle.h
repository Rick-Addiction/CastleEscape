// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"

#include "CastleEscape/Puzzles/Puzzle.h"
#include "BellsPuzzle.generated.h"


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
	TArray<AActor*> BellsToSolve;

	
	void PlayBellsToSolve(UMelodySphere* MelodySphere);
	
protected:
	UPROPERTY()
	TArray<UAudioComponent*> BellsAudioComponents;

	void StoreBellsToSolveAudioComponents();

	UFUNCTION()
	void PlayOneOfTheBellsToSolve(int BellIndex,UMelodySphere* MelodySphere);

};
