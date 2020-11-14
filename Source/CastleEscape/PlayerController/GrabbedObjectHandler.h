// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include <CastleEscape\PlayerController\GrabbedObject.h>
#include "GrabbedObjectHandler.generated.h"

UENUM(BlueprintType)
enum class EGrabbedObjectType : uint8 {
    PUZZLE_PIECE UMETA(DisplayName = "PUZZLE_PIECE"),
    GEM UMETA(DisplayName = "GEM"),
    UNDEFINED UMETA(DisplayName = "UNDEFINED")
};

UCLASS()
class CASTLEESCAPE_API UGrabbedObjectHandler : public UObject
{
    GENERATED_BODY()

    public:
    static class UGrabbedObjectHandler* MAKE(EGrabbedObjectType ObjectType, UPhysicsHandleComponent* PhysicsHandle, UGrabbedObject* GrabbedObject);

    virtual void MoveObject() { check(0 && "You must override this"); }
    virtual void InitHandler(UPhysicsHandleComponent* PhysicsHandle, UGrabbedObject* GrabbedObject) { check(0 && "You must override this"); }
    virtual void DestroyHandler() { check(0 && "You must override this"); }
    virtual void UpdatePuzzleSpace() { check(0 && "You must override this"); }

    void UpdateGrabbedObjectStatus(bool NewStatus);
   
    void SetPhysicsHandle(UPhysicsHandleComponent* PhysicsHandleToSet);
    void SetGrabbedObject(UGrabbedObject* GrabbedObjectToSet);
  
    FRotator GetCurrentGrabbedObjectRotation();

    protected:
    float Reach = 50.f;
    UPhysicsHandleComponent* PhysicsHandle = nullptr;
    UGrabbedObject* GrabbedObject = nullptr;
};

