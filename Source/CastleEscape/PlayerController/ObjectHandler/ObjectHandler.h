// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "ObjectHandler.generated.h"

UENUM(BlueprintType)
enum class EObjectType : uint8 {
    Jigsaw_Piece UMETA(DisplayName = "Jigsaw_Piece"),
    Gem UMETA(DisplayName = "Gem"),
    Bell UMETA(DisplayName = "Bell"),
    MelodySphere UMETA(DisplayName = "MelodySphere"),
    PipeValve UMETA(DisplayName = "PipeValve"),
    Undefined UMETA(DisplayName = "Undefined")
};

UCLASS()
class CASTLEESCAPE_API UObjectHandler : public UObject
{
    GENERATED_BODY()

    public:
    virtual void SetupInputComponent() { check(0 && "You must override this"); }
    virtual void Handle() { check(0 && "You must override this"); }

    static EObjectType GetObjectType(AActor* ObjectSought);


    
};

