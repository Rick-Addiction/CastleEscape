// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include <CastleEscape\PuzzlePiece.h>
#include "Components/ActorComponent.h"
#include "JigsawPiece.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UJigsawPiece : public UPuzzlePiece
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJigsawPiece();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	float GetNextRotationRoll();
	float GetCurrentRotationRoll();
	
private:

	void PlacePieceInPuzzleSpace() override;



	TArray<float> PossibleRotation = { 0.f,90.f,180.f,270.f };
	int CurrentPossibleRotationIndex = 0;
	int LastPossibleRotationIndex = 3;


	
		
};
