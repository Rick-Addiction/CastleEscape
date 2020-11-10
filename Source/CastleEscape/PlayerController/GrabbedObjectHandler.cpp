// Copyright Henrique Rachti Assumpção 2020

#include "GrabbedObjectHandler.h"
#include <CastleEscape\Puzzles\Jigsaw Puzzle\JigsawPieceHandler.h>
#include <CastleEscape\Puzzles\Gems Puzzle\GemHandler.h>

UGrabbedObjectHandler* UGrabbedObjectHandler::MAKE(EGrabbedObjectType ObjectType, UPhysicsHandleComponent* PhysicsHandle, UGrabbedObject* GrabbedObject)
{    
    UGrabbedObjectHandler* GrabbedObjectHandler;
    if (ObjectType == EGrabbedObjectType::PUZZLE_PIECE) {
        GrabbedObjectHandler = NewObject<UJigsawPieceHandler>(UJigsawPieceHandler::StaticClass());
        GrabbedObjectHandler->InitHandler(PhysicsHandle,GrabbedObject);
        return GrabbedObjectHandler;
    }
    else if(ObjectType == EGrabbedObjectType::GEM){
        GrabbedObjectHandler = NewObject<UGemHandler>(UGemHandler::StaticClass());
        GrabbedObjectHandler->PhysicsHandle = PhysicsHandle;
        return GrabbedObjectHandler;
    }
    else
        return nullptr;
}

void UGrabbedObjectHandler::SetPhysicsHandle(UPhysicsHandleComponent* PhysicsHandleToSet) {
    if (PhysicsHandleToSet) {
        PhysicsHandle = PhysicsHandleToSet;
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("You tried to set a NULL UPhysicsHandleComponent to the GrabbedObjectHandler"));
    }

    
}

void UGrabbedObjectHandler::SetGrabbedObject(UGrabbedObject* GrabbedObjectToSet) {
    if(GrabbedObjectToSet){
        GrabbedObject = GrabbedObjectToSet;
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("You tried to set a NULL GrabbedObjectToSet to the GrabbedObjectHandler"));
    }
}

void UGrabbedObjectHandler::UpdateGrabbedObjectStatus(bool NewStatus) {
    if (!GrabbedObject) { return; }

    GrabbedObject->SetGrabbedByPlayer(NewStatus);
}

FRotator UGrabbedObjectHandler::GetCurrentGrabbedObjectRotation() {
    
    FVector CurrentLocation;
    FRotator CurrentRotation;    
    
    if (PhysicsHandle)
    PhysicsHandle->GetTargetLocationAndRotation(OUT CurrentLocation, OUT CurrentRotation);

    return CurrentRotation;
}