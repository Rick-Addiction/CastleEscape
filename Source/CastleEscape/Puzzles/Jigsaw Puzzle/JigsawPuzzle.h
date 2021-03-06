// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"

#include "JigsawPiece.h"
#include "Engine/TriggerVolume.h"
#include "CastleEscape/Puzzles/Puzzle.h"
#include "JigsawPuzzle.generated.h"


USTRUCT(BlueprintType)
struct FJigsawPieceSpaceState
{
    GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATriggerVolume* JigsawPieceSpace;

    UPROPERTY()
    UJigsawPiece* CurrentJigsawPiecePlaced = nullptr;

    UPROPERTY()
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
    TArray<ATriggerVolume*> JigsawPieceSpaces;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<AActor*> JigsawPieces;
    
    UPROPERTY(EditAnywhere)
    USoundBase* PlaceJigsawPieceSound = nullptr;    

    virtual void SetCurrentPuzzlePiecePlaced(ATriggerVolume* JigsawPieceSpace, UActorComponent* JigsawPiecePlaced) override;
    virtual bool IsPuzzleSpaceAvailable(ATriggerVolume* JigsawPieceSpaceToCheck) override;
    virtual void SetPuzzleSpaceAvailability(ATriggerVolume* JigsawPieceSpace, bool bJigsawPieceSpaceAvailability) override;
	virtual void CheckIfItHasBeenSolved() override;

	virtual bool IsAllSpacesUnavailable() override;	
	
    void SettingJigsawPieces();
	void SettingJigsawPieceSpaces();

	private:
	
	UPROPERTY()
	TArray<FJigsawPieceSpaceState> JigsawPieceSpacesStates;
    
};
