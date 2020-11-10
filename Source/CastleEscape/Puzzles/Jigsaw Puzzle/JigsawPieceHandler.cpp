// Copyright Henrique Rachti Assumpção 2020

#include "JigsawPieceHandler.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include <CastleEscape\PlayerController\Grabber.h>

UJigsawPieceHandler::UJigsawPieceHandler()
{
	
}

void UJigsawPieceHandler::InitHandler(UPhysicsHandleComponent* PhysicsHandle,UGrabbedObject* GrabbedObject) {

	SetPhysicsHandle(PhysicsHandle);
	SetGrabbedObject(GrabbedObject);
	SetInitialRotation();
	SetupInputComponent();
	UpdateGrabbedObjectStatus(true);	
}

void UJigsawPieceHandler::DestroyHandler() {
	UpdateGrabbedObjectStatus(false);

	if (InputComponent) {
		InputComponent->RemoveActionBinding("Spin", IE_Pressed);
	}

	PhysicsHandle = nullptr;
	GrabbedObject = nullptr;
	InputComponent = nullptr;
}

void UJigsawPieceHandler::SetupInputComponent() {
	InputComponent = UGrabber::World->GetFirstPlayerController()->FindComponentByClass<UInputComponent>();

	if (InputComponent) {
		InputComponent->BindAction("Spin", IE_Pressed, this, &UJigsawPieceHandler::SpinJigsawPiece);		
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("InputComponent isn't attached in %s"), *GetWorld()->GetFirstPlayerController()->GetOwner()->GetName())
	}
}

void UJigsawPieceHandler::SetInitialRotation(){
	if (!PhysicsHandle) { return; }
	if (!GrabbedObject) { return; }

	FRotator InitialPuzzlePieceRotation = UGrabber::GetPlayersRotation();
	InitialPuzzlePieceRotation.Roll = ((UJigsawPiece*)GrabbedObject)->GetCurrentRotationRoll();
	PhysicsHandle->SetTargetRotation(InitialPuzzlePieceRotation);
}

void UJigsawPieceHandler::MoveObject()
{
	if (!PhysicsHandle) { return; }

	PhysicsHandle->SetTargetLocation(UGrabber::GetPlayersReachPos(Reach));

	FRotator NewGrabbedObjectRotation = GetCurrentGrabbedObjectRotation();
	NewGrabbedObjectRotation.Pitch = UGrabber::GetPlayersRotation().Pitch;
	NewGrabbedObjectRotation.Yaw = UGrabber::GetPlayersRotation().Yaw;
	PhysicsHandle->SetTargetRotation(NewGrabbedObjectRotation);

	UpdatePuzzleSpace();
}

void UJigsawPieceHandler::UpdatePuzzleSpace() {
	if (!GrabbedObject) { return; }

	FHitResult PuzzleSpace = UGrabber::GetFirstPuzzleSpaceInReach(Reach);

	if (PuzzleSpace.GetActor() != nullptr) {
		((UJigsawPiece*)GrabbedObject)->SetPuzzleSpace(PuzzleSpace.GetActor());
	}
	else {
		((UJigsawPiece*)GrabbedObject)->SetPuzzleSpace(nullptr);
	}
}

void UJigsawPieceHandler::SpinJigsawPiece() {
	if (!PhysicsHandle) { return; }
	if (!GrabbedObject) { return; }

	FRotator CurrentGrabbedObjectRotation = GetCurrentGrabbedObjectRotation();
	CurrentGrabbedObjectRotation.Roll = ((UJigsawPiece*)GrabbedObject)->GetNextRotationRoll();
	PhysicsHandle->SetTargetRotation(CurrentGrabbedObjectRotation);
}

