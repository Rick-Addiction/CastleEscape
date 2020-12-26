// Copyright Henrique Rachti Assumpção 2020

#include "InteractableObjectHandler.h"

#include "Puzzles/Bells Puzzle/BellsHandler.h"

UInteractableObjectHandler* UInteractableObjectHandler::Make(AActor* InteractedObject)
{
	const EObjectType ObjectType = GetObjectType(InteractedObject);
	
	UInteractableObjectHandler* InteractableObjectHandler;

	UE_LOG(LogTemp,Warning,TEXT("Trying to create Bells handler"));
	
	if (ObjectType == EObjectType::Bell) {
		UE_LOG(LogTemp,Warning,TEXT("Bells handler created"));
		InteractableObjectHandler = NewObject<UBellsHandler>(UBellsHandler::StaticClass());
		InteractableObjectHandler->InitHandler(InteractedObject);
        
		return InteractableObjectHandler;
	}
	else
		return nullptr;
}
