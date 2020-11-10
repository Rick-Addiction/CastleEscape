// Copyright Henrique Rachti Assumpção 2020
#pragma once

#include "CoreMinimal.h"
#include <CastleEscape\PlayerController\GrabbedObjectHandler.h>
#include "GemHandler.generated.h"

UCLASS()
class CASTLEESCAPE_API UGemHandler : public UGrabbedObjectHandler
{
	GENERATED_BODY()

public:
	UGemHandler();
	void MoveObject() override;
};
