// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CastleEscape/PlayerController/GrabbedObject.h"
#include "GrabbedObjectHandler.generated.h"

UENUM(BlueprintType)
enum class EGrabbedObjectType : uint8 {
    Puzzle_Piece UMETA(DisplayName = "Puzzle_Piece"),
    Gem UMETA(DisplayName = "Gem"),
    Undefined UMETA(DisplayName = "Undefined")
};

UCLASS()
class CASTLEESCAPE_API UGrabbedObjectHandler : public UObject
{
    GENERATED_BODY()

    public:
    static class UGrabbedObjectHandler* Make(EGrabbedObjectType ObjectType, UPhysicsHandleComponent* PhysicsHandle, UGrabbedObject* GrabbedObject);

    virtual void MoveObject() { check(0 && "You must override this"); }
    virtual void InitHandler(UPhysicsHandleComponent* PhysicsHandleToInit, UGrabbedObject* GrabbedObjectToInit) { check(0 && "You must override this"); }
    virtual void DestroyHandler() { check(0 && "You must override this"); }
    virtual void UpdatePuzzleSpace() { check(0 && "You must override this"); }

    void UpdateGrabbedObjectStatus(bool NewStatus) const;
   
    void SetPhysicsHandle(UPhysicsHandleComponent* PhysicsHandleToSet);
    void SetGrabbedObject(UGrabbedObject* GrabbedObjectToSet);
  
    FRotator GetCurrentGrabbedObjectRotation() const;

    protected:
    float Reach = 90.f;

    UPROPERTY()
    UPhysicsHandleComponent* PhysicsHandleUsed = nullptr;

    UPROPERTY()
    UGrabbedObject* CurrentGrabbedObject = nullptr;
};

