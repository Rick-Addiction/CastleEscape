// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "ObjectHandler.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CastleEscape/PlayerController/GrabbableObject.h"
#include "GrabbableObjectHandler.generated.h"



UCLASS()
class CASTLEESCAPE_API UGrabbableObjectHandler : public UObjectHandler
{
    GENERATED_BODY()

    public:
    static class UGrabbableObjectHandler* Make(AActor* GrabbedObject);

    virtual void MoveObject() { check(0 && "You must override this"); }
    virtual void InitHandler(AActor* GrabbedObjectToInit) { check(0 && "You must override this"); }
    virtual void DestroyHandler() { check(0 && "You must override this"); }
    virtual void UpdatePuzzleSpace() { check(0 && "You must override this"); }

    void UpdateGrabbedObjectStats(bool NewStats) const;
    static void Grab(AActor* GrabbedObject);
    void Release();   
    void SetGrabbedObject(UGrabbableObject* GrabbedObjectToSet);
    virtual void SetupInputComponent() override;
  
    static FRotator GetCurrentGrabbedObjectRotation();

    protected:
    float Reach = 90.f;

    UPROPERTY()
    UGrabbableObject* CurrentGrabbedObject = nullptr;

    
};

