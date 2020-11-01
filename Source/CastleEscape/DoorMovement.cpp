// Copyright Henrique Rachti Assumpção 2020

#include "DoorMovement.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/TriggerVolume.h"

#define OUT

// Sets default values for this component's properties
UDoorMovement::UDoorMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UDoorMovement::BeginPlay()
{
	Super::BeginPlay();

	FindAudioComponent();

	ClosedYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = ClosedYaw;
	OpenedYaw += CurrentYaw;

	
}


// Called every frame
void UDoorMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
		if(DoorStatus == EDoorStatus::OPEN){			
			if (CurrentYaw > OpenedYaw) {
				DoorStatus = EDoorStatus::NONE;
			}
			else {
				OpenDoor(DeltaTime);
			}
		}
		else if(DoorStatus == EDoorStatus::CLOSE) {
			if (CurrentYaw < ClosedYaw) {
				DoorStatus = EDoorStatus::NONE;
			}
			else {
				CloseDoor(DeltaTime);
			}
		}
}

void UDoorMovement::FindAudioComponent() {

	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!AudioComponent) {

		UE_LOG(LogTemp, Error, TEXT("AudioComponent isn't attached in %s"), *GetOwner()->GetName())
	}
}


void UDoorMovement::MoveDoor(float DeltaTime, float TargetYaw, float Speed)
{
		CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw , DeltaTime, Speed);

		FRotator CurrentRotation = GetOwner()->GetActorRotation();
		CurrentRotation.Yaw = CurrentYaw;

		GetOwner()->SetActorRotation(CurrentRotation);

}

void UDoorMovement::OpenDoor(float DeltaTime)
{
	if (AudioComponent) {
		DoorClosed = false;
		if (!DoorOpened) {
			AudioComponent->Play();
			DoorOpened = true;
		}
	}
	
	MoveDoor(DeltaTime, OpenedYaw+2,OpenDoorSpeed);
}

void UDoorMovement::CloseDoor(float DeltaTime)
{

	if (AudioComponent) {
		DoorOpened = false;
		if (!DoorClosed) {
			AudioComponent->Play();
			DoorClosed = true;
		}
	}

	MoveDoor(DeltaTime, ClosedYaw-2,CloseDoorSpeed);
}

void UDoorMovement::SetDoorMovement(EDoorStatus NewDoorStatus) {
	
	if (LastDoorStatus != NewDoorStatus) {
		DoorStatus = NewDoorStatus;
		LastDoorStatus = NewDoorStatus;
	}
}
