// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "CastleEscape/PlayerController/GrabbableObject.h"
#include "GemsPuzzleMediator.h"
#include "Gem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UGem : public UGrabbableObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FColor GetGemColor();
	void SetPlaceGemAudioComponent(USoundBase* PlaceGemSound);

	UGemsPuzzleMediator* GetPuzzleManager() const;
	void SetPuzzleManager(UGemsPuzzleMediator* PuzzleManagerToSet);

	UPROPERTY()
	UGemsPuzzleMediator* PuzzleManager = nullptr;
	
private:

	virtual void PlacePuzzleObjectInPuzzleSpace() override;
	virtual void RemovePuzzleObjectFromPuzzleSpace() override;

	UPROPERTY()
	UAudioComponent* PlaceGemAudioComponent = nullptr;

};
