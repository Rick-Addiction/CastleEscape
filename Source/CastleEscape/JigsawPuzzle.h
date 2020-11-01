// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include <CastleEscape\CastleEscape.h>
#include "JigsawPuzzle.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UJigsawPuzzle : public UActorComponent
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
	TArray<FPuzzleSpace> PuzzleSpaceArray;

	bool CheckIfPuzzleSpaceIsAvailable(AActor* PuzzleSpaceToCheck);

	void SetPuzzleSpaceAvailability(AActor* PuzzleSpace, bool PuzzleSpaceAvailability);

	void SetPuzzlePieceRotation(AActor* PuzzleSpace,int PieceRotationIndex);

	void SetCurrentPuzzlePiecePlaced(AActor* PuzzleSpace, AActor* PuzzlePiecePlaced);

	void CheckIfItHasBeenSolved();

	bool CheckIfAllSpacesHasAPuzzle();

	float MyDeltaTime;
		
};
