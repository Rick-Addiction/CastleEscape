// Copyright Henrique Rachti Assumpção 2020


#include "BellsHandler.h"

#include "Bell.h"

UBellsHandler::UBellsHandler()
{
	
}

void UBellsHandler::InitHandler(AActor* InteractedObjectToInit) {

	SetInteractedObject(InteractedObjectToInit->FindComponentByClass<UBell>());
}

void UBellsHandler::DestroyHandler() {

	CurrentInteractableObject = nullptr;
}

void UBellsHandler::Handle()
{
	if (!IsBellPlaying)
	{
		static_cast<UBell*>(CurrentInteractableObject)->PlayBell();
		IsBellPlaying = true;
	}
}

void UBellsHandler::SetInteractedObject(UInteractableObject* InteractedObjectToSet)
{
	CurrentInteractableObject = InteractedObjectToSet;
}


