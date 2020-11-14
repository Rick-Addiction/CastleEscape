// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include <CastleEscape\Puzzles\Puzzle.h>
#include "JigsawPuzzle.generated.h"

UENUM(BlueprintType)
enum class EPuzzleRotation : uint8 {
    UP UMETA(DisplayName = "UP"),
    LEFT UMETA(DisplayName = "LEFT"),
    DOWN UMETA(DisplayName = "DOWN"),
    RIGHT UMETA(DisplayName = "RIGHT")
};

USTRUCT(BlueprintType)
struct FJigsawPieceSpace
{
    GENERATED_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ATriggerVolume* PuzzleSpace;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        AActor* PuzzlePieceExpected;

    AActor* CurrentPuzzlePiecePlaced;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        EPuzzleRotation PuzzlePieceRotationExpected;

    EPuzzleRotation CurrentPuzzlePieceRotation;

    bool bAvailable = true;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UJigsawPuzzle : public UPuzzle
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UJigsawPuzzle();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<FJigsawPieceSpace> JigsawPieceSpaces;

    virtual void SetCurrentPuzzlePiecePlaced(AActor* PuzzleSpace, AActor* PuzzlePiecePlaced) override;

    virtual bool CheckIfPuzzleSpaceIsAvailable(AActor* PuzzleSpaceToCheck) override;

    virtual void SetPuzzleSpaceAvailability(AActor* PuzzleSpace, bool PuzzleSpaceAvailability) override;

	virtual void CheckIfItHasBeenSolved() override;

	virtual bool CheckIfAllSpacesHasAPuzzle() override;

    void SetPuzzlePieceRotation(AActor* PuzzleSpace, int PieceRotationIndex);
		
};
