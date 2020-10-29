// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include <CastleEscape\CastleEscape.h>
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
	TArray<ATriggerVolume*> ATriggerVolumeArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPuzzleSpace> PuzzleSpaceArray;


	bool CheckIfPuzzleSpaceIsAvailable(AActor* PuzzleSpaceToCheck);

	void SetPuzzleSpaceAvailability(AActor* PuzzleSpace, bool PuzzleSpaceAvailability);

		
};
