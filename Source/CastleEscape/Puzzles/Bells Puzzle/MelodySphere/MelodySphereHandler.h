// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "PlayerController/ObjectHandler/InteractableObjectHandler.h"
#include "MelodySphereHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UMelodySphereHandler : public UInteractableObjectHandler
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMelodySphereHandler();

	virtual void Handle() override;

	virtual void InitHandler(AActor* InteractedObjectToInit) override;
	virtual void DestroyHandler() override;

	virtual void SetInteractedObject(UInteractableObject* InteractedObjectToSet) override;

	private:
	bool IsBellPlaying = false;
};
