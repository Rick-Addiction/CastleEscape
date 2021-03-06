// Copyright Henrique Rachti Assumpção 2020


#include "PipeValveHandler.h"
#include "PipeValve.h"

UPipeValveHandler::UPipeValveHandler()
{
	
}

void UPipeValveHandler::InitHandler(AActor* InteractedObjectToInit) {

	SetInteractedObject(InteractedObjectToInit->FindComponentByClass<UPipeValve>());
}

void UPipeValveHandler::DestroyHandler() {

	CurrentInteractableObject = nullptr;
}

void UPipeValveHandler::Handle()
{
	static_cast<UPipeValve*>(CurrentInteractableObject)->Play();
}

void UPipeValveHandler::SetInteractedObject(UInteractableObject* InteractedObjectToSet)
{
	CurrentInteractableObject = InteractedObjectToSet;
}


