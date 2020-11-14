// Copyright Henrique Rachti Assumpção 2020

#include "GemHandler.h"
#include <CastleEscape\PlayerController\Grabber.h>

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

	PhysicsHandle = nullptr;
	GrabbedObject = nullptr;
}

void UGemHandler::MoveObject()
{
	if (!PhysicsHandle) { return; }

	PhysicsHandle->SetTargetLocation(UGrabber::GetPlayersReachPos(Reach));

	FRotator NewGrabbedObjectRotation = UGrabber::GetPlayersRotation();
	NewGrabbedObjectRotation.Pitch += 90;
	PhysicsHandle->SetTargetRotation(NewGrabbedObjectRotation);

	UpdatePuzzleSpace();
}

void UGemHandler::UpdatePuzzleSpace() {
	if (!GrabbedObject) { return; }

	FHitResult PuzzleSpace = UGrabber::GetFirstPuzzleSpaceInReach(100.f);

	if (PuzzleSpace.GetActor() != nullptr) {
		((UGem*)GrabbedObject)->SetPuzzleSpace(PuzzleSpace.GetActor());
	}
	else {
		((UGem*)GrabbedObject)->SetPuzzleSpace(nullptr);
	}
}