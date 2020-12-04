// Copyright Henrique Rachti Assumpção 2020

#include "GrabbableObjectHandler.h"
#include "CastleEscape/Puzzles/Jigsaw Puzzle/JigsawPieceHandler.h"
#include "CastleEscape/Puzzles/Gems Puzzle/GemHandler.h"
#include "PlayerController/PlayerCharacter.h"
#include "Puzzles/Gems Puzzle/Gem.h"

UGrabbableObjectHandler* UGrabbableObjectHandler::Make(AActor* GrabbedObject)
{
	const EObjectType ObjectType = GetObjectType(GrabbedObject);
	
    UGrabbableObjectHandler* GrabbedObjectHandler;
    if (ObjectType == EObjectType::Jigsaw_Piece) {
    	Grab(GrabbedObject);
        GrabbedObjectHandler = NewObject<UJigsawPieceHandler>(UJigsawPieceHandler::StaticClass());
        GrabbedObjectHandler->InitHandler(GrabbedObject);
        
        return GrabbedObjectHandler;
    }
    else if(ObjectType == EObjectType::Gem){
    	Grab(GrabbedObject);
        GrabbedObjectHandler = NewObject<UGemHandler>(UGemHandler::StaticClass());
        GrabbedObjectHandler->InitHandler(GrabbedObject);
        return GrabbedObjectHandler;
    }
    else
        return nullptr;
}


void UGrabbableObjectHandler::Grab(AActor* GrabbedObject) {
	UPhysicsHandleComponent* PhysicsHandle = UPlayerCharacter::GetPhysicsHandle();
	if (!PhysicsHandle) { return; }

		UPrimitiveComponent* GrabbedObjectPrimitiveComponent = GrabbedObject->FindComponentByClass<UPrimitiveComponent>();

		if(GrabbedObjectPrimitiveComponent)
		{
			PhysicsHandle->GrabComponentAtLocationWithRotation
         (GrabbedObjectPrimitiveComponent,
             NAME_None,
             GrabbedObject->GetActorLocation(),
             GrabbedObject->GetActorRotation()
         );	
			GrabbedObjectPrimitiveComponent->GetBodyInstance()->bLockXTranslation = false;
			GrabbedObjectPrimitiveComponent->GetBodyInstance()->bLockYTranslation= false;
			GrabbedObjectPrimitiveComponent->GetBodyInstance()->bLockZTranslation= false;
			GrabbedObjectPrimitiveComponent->GetBodyInstance()->bLockXRotation = false;
			GrabbedObjectPrimitiveComponent->GetBodyInstance()->bLockYRotation= false;
			GrabbedObjectPrimitiveComponent->GetBodyInstance()->bLockZRotation= false;
			GrabbedObjectPrimitiveComponent->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);
		}
	
}

void UGrabbableObjectHandler::Release() {
	UPhysicsHandleComponent* PhysicsHandle = UPlayerCharacter::GetPhysicsHandle();
	
	if (!PhysicsHandle) { return; }
	if (!PhysicsHandle->GrabbedComponent) { return; }

	UE_LOG(LogTemp, Error, TEXT("RELEASE OBJECT"))
	
	UPrimitiveComponent* GrabbedObjectPrimitiveComponent = PhysicsHandle->GrabbedComponent->GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	GrabbedObjectPrimitiveComponent->GetBodyInstance()->bLockXTranslation = true;
	GrabbedObjectPrimitiveComponent->GetBodyInstance()->bLockYTranslation= true;
	GrabbedObjectPrimitiveComponent->GetBodyInstance()->bLockZTranslation= false;
	GrabbedObjectPrimitiveComponent->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);

	DestroyHandler();
	PhysicsHandle->ReleaseComponent();
}


void UGrabbableObjectHandler::SetGrabbedObject(UGrabbableObject* GrabbedObjectToSet) {
    if(GrabbedObjectToSet){
        CurrentGrabbedObject = GrabbedObjectToSet;        
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("You tried to set a NULL GrabbedObjectToSet to the GrabbedObjectHandler"));
    }
}

void UGrabbableObjectHandler::UpdateGrabbedObjectStats(bool NewStats) const {
    if (!CurrentGrabbedObject) { return; }

    CurrentGrabbedObject->SetGrabbedByPlayer(NewStats);
}

 FRotator UGrabbableObjectHandler::GetCurrentGrabbedObjectRotation(){    
    FVector CurrentLocation;
    FRotator CurrentRotation;

	UPhysicsHandleComponent* PhysicsHandle = UPlayerCharacter::GetPhysicsHandle();
    
    if (PhysicsHandle)
    PhysicsHandle->GetTargetLocationAndRotation(OUT CurrentLocation, OUT CurrentRotation);

    return CurrentRotation;
}

