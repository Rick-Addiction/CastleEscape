// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include <CastleEscape\PlayerController\GrabbedObject.h>
#include "Components/ActorComponent.h"
#include "Gem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UGem : public UGrabbedObject
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

	FLinearColor GetGemColor();
private:

	void PlacePieceInPuzzleSpace() override;
	void RemovePieceFromPuzzleSpace() override;
	
	

};
