// Copyright Henrique Rachti Assumpção 2020

#include "InteractableObjectHandler.h"

#include "Puzzles/Bells Puzzle/Bell/BellsHandler.h"
#include "Puzzles/Bells Puzzle/MelodySphere/MelodySphereHandler.h"
#include "Puzzles/Pipes Puzzle/PipeValveHandler.h"

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
	else if (ObjectType == EObjectType::MelodySphere)
	{
		UE_LOG(LogTemp,Warning,TEXT("MelodySphere handler created"));
		InteractableObjectHandler = NewObject<UMelodySphereHandler>(UMelodySphereHandler::StaticClass());
		InteractableObjectHandler->InitHandler(InteractedObject);
        
		return InteractableObjectHandler;		
	}
	else if (ObjectType == EObjectType::PipeValve)
	{
		UE_LOG(LogTemp,Warning,TEXT("PipeValve handler created"));
		InteractableObjectHandler = NewObject<UPipeValveHandler>(UPipeValveHandler::StaticClass());
		InteractableObjectHandler->InitHandler(InteractedObject);
        
		return InteractableObjectHandler;		
	}
	else 
		return nullptr;
}
