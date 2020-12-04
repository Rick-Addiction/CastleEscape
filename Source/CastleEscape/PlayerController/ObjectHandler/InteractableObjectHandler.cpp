// Copyright Henrique Rachti Assumpção 2020

#include "InteractableObjectHandler.h"

#include "PlayerController/PlayerCharacter.h"

UInteractableObjectHandler* UInteractableObjectHandler::Make(AActor* InteractedObject)
{
	UInteractableObjectHandler* InteractableObjectHandler =NewObject<UInteractableObjectHandler>(UInteractableObjectHandler::StaticClass());
     return InteractableObjectHandler;
}

void UInteractableObjectHandler::SetupInputComponent() {
	UInputComponent* InputComponent = UPlayerCharacter::GetInputComponent();
	if (InputComponent) {
		InputComponent->BindAction("Interact", IE_Pressed, this, &UInteractableObjectHandler::Interact);	
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("InputComponent isn't attached"))
	}
}


void UInteractableObjectHandler::Handle() {	

	Interact();
		
}

void UInteractableObjectHandler::Interact() {	

	UE_LOG(LogTemp, Error, TEXT("Object has received an interaction"))
		
}









