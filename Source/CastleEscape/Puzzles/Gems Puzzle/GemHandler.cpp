// Copyright Henrique Rachti Assumpção 2020

#include "GemHandler.h"
#include "CastleEscape/PlayerController/Grabber.h"

UGemHandler::UGemHandler()
{

}

void UGemHandler::InitHandler(UPhysicsHandleComponent* PhysicsHandle, UGrabbedObject* GrabbedObject) {

	SetPhysicsHandle(PhysicsHandle);
	SetGrabbedObject(GrabbedObject);
	UpdateGrabbedObjectStatus(true);
}

void UGemHandler::DestroyHandler() {
	UpdateGrabbedObjectStatus(false);

	PhysicsHandleUsed = nullptr;
	CurrentGrabbedObject = nullptr;
}

void UGemHandler::MoveObject()
{
	if (!PhysicsHandleUsed) { return; }
	
	if(PhysicsHandleUsed->GetGrabbedComponent())
	{
		PhysicsHandleUsed->SetTargetLocation(UGrabber::GetPlayersReachPos(50.f));

		FRotator NewGrabbedObjectRotation = UGrabber::GetPlayersRotation();
		NewGrabbedObjectRotation.Pitch += 90;
		PhysicsHandleUsed->SetTargetRotation(NewGrabbedObjectRotation);
	}
	UpdatePuzzleSpace();
}

void UGemHandler::UpdatePuzzleSpace() {
	if (!CurrentGrabbedObject) { return; }

	const FHitResult PuzzleSpace = UGrabber::GetFirstPuzzleSpaceInReach(DistanceToSearchForPuzzleSpaces);

	if (PuzzleSpace.GetActor()) {

		if(static_cast<UGem*>(CurrentGrabbedObject)->GetPuzzleManager())
		{
			static_cast<UGem*>(CurrentGrabbedObject)->SetPuzzle((static_cast<UGem*>(CurrentGrabbedObject))->GetPuzzleManager()->GetGemsPuzzleByPuzzleSpace(static_cast<ATriggerVolume*>(PuzzleSpace.GetActor())));
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("No Puzzle Managerrt"));	
		}
		
		static_cast<UGem*>(CurrentGrabbedObject)->SetPuzzleSpace(static_cast<ATriggerVolume*>(PuzzleSpace.GetActor()));
	}
	else {
		static_cast<UGem*>(CurrentGrabbedObject)->SetPuzzleSpace(nullptr);		
	}
}