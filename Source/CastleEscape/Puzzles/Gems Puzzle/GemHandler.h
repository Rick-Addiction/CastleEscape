// Copyright Henrique Rachti Assumpção 2020
#pragma once

#include "CoreMinimal.h"
#include "PlayerController/ObjectHandler/GrabbableObjectHandler.h"
#include "GemHandler.generated.h"

class UGemsPuzzle;
UCLASS()
class CASTLEESCAPE_API UGemHandler : public UGrabbableObjectHandler
{
	GENERATED_BODY()

public:
	UGemHandler();
	virtual void Handle() override;
	virtual void MoveObject() override;
	virtual void InitHandler(AActor* GrabbedObject) override;
	virtual void DestroyHandler() override;
	virtual void UpdatePuzzleSpace() override;

private:
	UGemsPuzzle* CurrentStatue = nullptr;
	float DistanceToSearchForPuzzleSpaces = 100.f;
};
