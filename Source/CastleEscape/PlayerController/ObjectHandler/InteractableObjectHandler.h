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

    virtual void MoveObject() { check(0 && "You must override this"); }
    virtual void InitHandler(AActor* InteractedObjectToInit) { check(0 && "You must override this"); }
    virtual void DestroyHandler() { check(0 && "You must override this"); }
    virtual void SetInteractedObject(UInteractableObject* InteractedObjectToSet){ check(0 && "You must override this"); }
  
    protected:
    float Reach = 90.f;

    UPROPERTY()
    UInteractableObject* CurrentInteractableObject = nullptr;
};

