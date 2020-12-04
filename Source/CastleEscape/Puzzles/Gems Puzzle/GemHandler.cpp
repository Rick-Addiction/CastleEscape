// Copyright Henrique Rachti Assumpção 2020

#include "GemHandler.h"

#include "Gem.h"
#include "PlayerController/PlayerCharacter.h"

UGemHandler::UGemHandler()
{

}

void UGemHandler::InitHandler(AActor* GrabbedObject) {

	SetGrabbedObject(GrabbedObject->FindComponentByClass<UGem>());
	SetupInputComponent();
	UpdateGrabbedObjectStats(true);
}

void UGrabbableObjectHandler::SetupInputComponent() {
	UInputComponent* InputComponent = UPlayerCharacter::GetInputComponent();
	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabbableObjectHandler::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("InputComponent isn't attached"))
	}
}

void UGemHandler::DestroyHandler() {
	UpdateGrabbedObjectStats(false);

	UInputComponent* InputComponent = UPlayerCharacter::GetInputComponent();
	if (InputComponent) {
		InputComponent->RemoveActionBinding("Grab", IE_Released);
	}


	CurrentGrabbedObject = nullptr;
}

void UGemHandler::Handle()
{
	MoveObject();
	UpdatePuzzleSpace();	
}


void UGemHandler::MoveObject()
{
	UPhysicsHandleComponent* PhysicsHandle = UPlayerCharacter::GetPhysicsHandle();
	if (!PhysicsHandle) { return; }
	
	if(PhysicsHandle->GetGrabbedComponent())
	{
		PhysicsHandle->SetTargetLocation(UPlayerCharacter::GetPlayersReachPos(50.f));

		FRotator NewGrabbedObjectRotation = UPlayerCharacter::GetPlayersRotation();
		NewGrabbedObjectRotation.Pitch += 90;
		PhysicsHandle->SetTargetRotation(NewGrabbedObjectRotation);
	}	
}

void UGemHandler::UpdatePuzzleSpace() {
	if (!CurrentGrabbedObject) { return; }

	const FHitResult PuzzleSpace = UPlayerCharacter::GetFirstPuzzleSpaceInReach(DistanceToSearchForPuzzleSpaces);

	if (PuzzleSpace.GetActor()) {

		if(static_cast<UGem*>(CurrentGrabbedObject)->GetPuzzleManager())
		{
			static_cast<UGem*>(CurrentGrabbedObject)->SetPuzzle((static_cast<UGem*>(CurrentGrabbedObject))->GetPuzzleManager()->GetGemsPuzzleByPuzzleSpace(static_cast<ATriggerVolume*>(PuzzleSpace.GetActor())));
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("No Puzzle Manager"));	
		}
		
		static_cast<UGem*>(CurrentGrabbedObject)->SetPuzzleSpace(static_cast<ATriggerVolume*>(PuzzleSpace.GetActor()));
	}
	else {
		static_cast<UGem*>(CurrentGrabbedObject)->SetPuzzleSpace(nullptr);		
	}
}