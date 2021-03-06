// Copyright Henrique Rachti Assumpção 2020


#include "MelodySphereHandler.h"

#include "MelodySphere.h"


UMelodySphereHandler::UMelodySphereHandler()
{
	
}

void UMelodySphereHandler::InitHandler(AActor* InteractedObjectToInit) {

	SetInteractedObject(InteractedObjectToInit->FindComponentByClass<UMelodySphere>());
}

void UMelodySphereHandler::DestroyHandler() {

	CurrentInteractableObject = nullptr;
}

void UMelodySphereHandler::Handle()
{
	if (!IsBellPlaying)
	{
		static_cast<UMelodySphere*>(CurrentInteractableObject)->Play();
		IsBellPlaying = true;
	}
}

void UMelodySphereHandler::SetInteractedObject(UInteractableObject* InteractedObjectToSet)
{
	CurrentInteractableObject = InteractedObjectToSet;
}


