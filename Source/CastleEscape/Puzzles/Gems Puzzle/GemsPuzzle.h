// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Particles/Emitter.h"
#include <CastleEscape\Puzzles\Puzzle.h>
#include "GemsPuzzle.generated.h"

USTRUCT(BlueprintType)
struct FGemSpace
{
    GENERATED_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ATriggerVolume* PuzzleSpace;

    AActor* CurrentGemPlaced = nullptr;

    bool bAvailable = true;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UGemsPuzzle : public UPuzzle
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGemsPuzzle();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGemSpace> GemSpaces;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AEmitter* TorchFire;

	virtual void SetCurrentPuzzlePiecePlaced(AActor* PuzzleSpace, AActor* PuzzlePiecePlaced) override;

	virtual bool CheckIfPuzzleSpaceIsAvailable(AActor* GemSpaceToCheck) override;

	virtual void SetPuzzleSpaceAvailability(AActor* GemSpace, bool GemSpaceAvailability) override;

	virtual void CheckIfItHasBeenSolved() override;

	virtual bool CheckIfAllSpacesHasAPuzzle() override;

	void UpdateTorchFireColor();

		
};
