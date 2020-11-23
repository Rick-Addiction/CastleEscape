// Copyright Henrique Rachti Assumpção 2020

#include "GrabbedObjectHandler.h"
#include <CastleEscape\Puzzles\Jigsaw Puzzle\JigsawPieceHandler.h>
#include <CastleEscape\Puzzles\Gems Puzzle\GemHandler.h>

UGrabbedObjectHandler* UGrabbedObjectHandler::Make(EGrabbedObjectType ObjectType, UPhysicsHandleComponent* PhysicsHandle, UGrabbedObject* GrabbedObject)
{    
    UGrabbedObjectHandler* GrabbedObjectHandler;
    if (ObjectType == EGrabbedObjectType::Puzzle_Piece) {
        GrabbedObjectHandler = NewObject<UJigsawPieceHandler>(UJigsawPieceHandler::StaticClass());
        GrabbedObjectHandler->InitHandler(PhysicsHandle,GrabbedObject);
        
        return GrabbedObjectHandler;
    }
    else if(ObjectType == EGrabbedObjectType::Gem){
        GrabbedObjectHandler = NewObject<UGemHandler>(UGemHandler::StaticClass());
        GrabbedObjectHandler->InitHandler(PhysicsHandle, GrabbedObject);
        return GrabbedObjectHandler;
    }
    else
        return nullptr;
}

// Called every frame

void UGrabbedObjectHandler::SetPhysicsHandle(UPhysicsHandleComponent* PhysicsHandleToSet) {
    if (PhysicsHandleToSet) {
        PhysicsHandleUsed = PhysicsHandleToSet;
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("You tried to set a NULL UPhysicsHandleComponent to the GrabbedObjectHandler"));
    }
}

void UGrabbedObjectHandler::SetGrabbedObject(UGrabbedObject* GrabbedObjectToSet) {
    if(GrabbedObjectToSet){
        CurrentGrabbedObject = GrabbedObjectToSet;        
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("You tried to set a NULL GrabbedObjectToSet to the GrabbedObjectHandler"));
    }
}

void UGrabbedObjectHandler::UpdateGrabbedObjectStatus(bool NewStatus) const {
    if (!CurrentGrabbedObject) { return; }

    CurrentGrabbedObject->SetGrabbedByPlayer(NewStatus);
}

FRotator UGrabbedObjectHandler::GetCurrentGrabbedObjectRotation() const {    
    FVector CurrentLocation;
    FRotator CurrentRotation;   
    
    if (PhysicsHandleUsed)
    PhysicsHandleUsed->GetTargetLocationAndRotation(OUT CurrentLocation, OUT CurrentRotation);

    return CurrentRotation;
}

