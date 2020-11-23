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

	PhysicsHandleUsed = nullptr;
	CurrentGrabbedObject = nullptr;
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

void UJigsawPieceHandler::SetInitialRotation() const{
	if (!PhysicsHandleUsed) { return; }
	if (!CurrentGrabbedObject) { return; }

	FRotator InitialPuzzlePieceRotation = UGrabber::GetPlayersRotation();
	InitialPuzzlePieceRotation.Roll = static_cast<UJigsawPiece*>(CurrentGrabbedObject)->GetCurrentRotationRoll();
	PhysicsHandleUsed->SetTargetRotation(InitialPuzzlePieceRotation);
}

void UJigsawPieceHandler::MoveObject()
{
	if (!PhysicsHandleUsed) { return; }

	PhysicsHandleUsed->SetTargetLocation(UGrabber::GetPlayersReachPos(Reach));

	FRotator NewGrabbedObjectRotation = GetCurrentGrabbedObjectRotation();
	NewGrabbedObjectRotation.Pitch = UGrabber::GetPlayersRotation().Pitch;
	NewGrabbedObjectRotation.Yaw = UGrabber::GetPlayersRotation().Yaw;
	PhysicsHandleUsed->SetTargetRotation(NewGrabbedObjectRotation);

	UpdatePuzzleSpace();
}

void UJigsawPieceHandler::UpdatePuzzleSpace() {
	if (!CurrentGrabbedObject) { return; }

	const FHitResult PuzzleSpace = UGrabber::GetFirstPuzzleSpaceInReach(Reach);

	if (PuzzleSpace.GetActor() != nullptr) {
		static_cast<UJigsawPiece*>(CurrentGrabbedObject)->SetPuzzleSpace(static_cast<ATriggerVolume*>(PuzzleSpace.GetActor()));
		
	}
	else {
		static_cast<UJigsawPiece*>(CurrentGrabbedObject)->SetPuzzleSpace(nullptr);
	}
}

void UJigsawPieceHandler::SpinJigsawPiece(){
	if (!PhysicsHandleUsed) { return; }
	if (!CurrentGrabbedObject) { return; }

	FRotator CurrentGrabbedObjectRotation = GetCurrentGrabbedObjectRotation();
	CurrentGrabbedObjectRotation.Roll = static_cast<UJigsawPiece*>(CurrentGrabbedObject)->GetNextRotationRoll();
	PhysicsHandleUsed->SetTargetRotation(CurrentGrabbedObjectRotation);
}

