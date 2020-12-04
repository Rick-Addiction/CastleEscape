// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "ObjectHandler.h"
#include "PlayerController/InteractableObject.h"

#include "InteractableObjectHandler.generated.h"



UCLASS()
class CASTLEESCAPE_API UInteractableObjectHandler : public UObjectHandler
{
    GENERATED_BODY()

    public:
    static class UInteractableObjectHandler* Make(AActor* InteractedObject);

    virtual void Handle() override;
    virtual void MoveObject() { check(0 && "You must override this"); }
    virtual void InitHandler(UInteractableObject* InteractedObjectToInit) { check(0 && "You must override this"); }
    virtual void SetupInputComponent() override;
    virtual void DestroyHandler() { check(0 && "You must override this"); }
    virtual void UpdatePuzzleSpace() { check(0 && "You must override this"); }

    void Interact();
  
    protected:
    float Reach = 90.f;
};

