// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "PlayerController/ObjectHandler/InteractableObjectHandler.h"
#include "BellsHandler.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UBellsHandler : public UInteractableObjectHandler
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBellsHandler();

	virtual void Handle() override;

	virtual void InitHandler(AActor* InteractedObjectToInit) override;
	virtual void DestroyHandler() override;

	virtual void SetInteractedObject(UInteractableObject* InteractedObjectToSet) override;

	
};
