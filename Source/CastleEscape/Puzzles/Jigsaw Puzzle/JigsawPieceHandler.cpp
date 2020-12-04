// Copyright Henrique Rachti Assumpção 2020

#include "JigsawPieceHandler.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include <CastleEscape\PlayerController\ObjectSeeker.h>

#include "JigsawPiece.h"
#include "PlayerController/PlayerCharacter.h"

UJigsawPieceHandler::UJigsawPieceHandler()
{
	
}

void UJigsawPieceHandler::InitHandler(AActor* GrabbedObject) {

	SetGrabbedObject(GrabbedObject->FindComponentByClass<UJigsawPiece>());
	SetInitialRotation();
	SetupInputComponent();
	UpdateGrabbedObjectStats(true);	
}

void UJigsawPieceHandler::DestroyHandler() {
	UpdateGrabbedObjectStats(false);

	UInputComponent* InputComponent = UPlayerCharacter::GetInputComponent();
	if (InputComponent) {
		InputComponent->RemoveActionBinding("Spin", IE_Pressed);
		InputComponent->RemoveActionBinding("Grab", IE_Released);
	}

	CurrentGrabbedObject = nullptr;
	
}

void UJigsawPieceHandler::SetupInputComponent() {

	Super::SetupInputComponent();
	
	UInputComponent* InputComponent = UPlayerCharacter::GetInputComponent();

	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabbableObjectHandler::Release);
		InputComponent->BindAction("Spin", IE_Pressed, this, &UJigsawPieceHandler::SpinJigsawPiece);		
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("InputComponent isn't attached in %s"), *GetWorld()->GetFirstPlayerController()->GetOwner()->GetName())
	}
}

void UJigsawPieceHandler::SetInitialRotation() const{
	UPhysicsHandleComponent* PhysicsHandle = UPlayerCharacter::GetPhysicsHandle();
	if (!PhysicsHandle) { return; }
	if (!CurrentGrabbedObject) { return; }

	FRotator InitialPuzzlePieceRotation = UPlayerCharacter::GetPlayersRotation();
	InitialPuzzlePieceRotation.Roll = static_cast<UJigsawPiece*>(CurrentGrabbedObject)->GetCurrentRotationRoll();
	PhysicsHandle->SetTargetRotation(InitialPuzzlePieceRotation);
}

void UJigsawPieceHandler::Handle()
{
	MoveObject();
	UpdatePuzzleSpace();	
}

void UJigsawPieceHandler::MoveObject()
{
	UPhysicsHandleComponent* PhysicsHandle = UPlayerCharacter::GetPhysicsHandle();
	if (!PhysicsHandle) { return; }

	PhysicsHandle->SetTargetLocation(UPlayerCharacter::GetPlayersReachPos(Reach));

	FRotator NewGrabbedObjectRotation = GetCurrentGrabbedObjectRotation();
	NewGrabbedObjectRotation.Pitch = UPlayerCharacter::GetPlayersRotation().Pitch;
	NewGrabbedObjectRotation.Yaw = UPlayerCharacter::GetPlayersRotation().Yaw;
	PhysicsHandle->SetTargetRotation(NewGrabbedObjectRotation);	
}

void UJigsawPieceHandler::UpdatePuzzleSpace() {
	if (!CurrentGrabbedObject) { return; }

	const FHitResult PuzzleSpace = UPlayerCharacter::GetFirstPuzzleSpaceInReach(Reach);

	if (PuzzleSpace.GetActor() != nullptr) {
		static_cast<UJigsawPiece*>(CurrentGrabbedObject)->SetPuzzleSpace(static_cast<ATriggerVolume*>(PuzzleSpace.GetActor()));
		
	}
	else {
		static_cast<UJigsawPiece*>(CurrentGrabbedObject)->SetPuzzleSpace(nullptr);
	}
}

void UJigsawPieceHandler::SpinJigsawPiece(){
	UPhysicsHandleComponent* PhysicsHandle = UPlayerCharacter::GetPhysicsHandle();
	if (!PhysicsHandle) { return; }
	if (!CurrentGrabbedObject) { return; }

	FRotator CurrentGrabbedObjectRotation = GetCurrentGrabbedObjectRotation();
	CurrentGrabbedObjectRotation.Roll = static_cast<UJigsawPiece*>(CurrentGrabbedObject)->GetNextRotationRoll();
	PhysicsHandle->SetTargetRotation(CurrentGrabbedObjectRotation);
}

