// Copyright Henrique Rachti Assumpção 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerVolume.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;



	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();


	if (ActorThatOpens == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("%s don't have a ActorThatOpen attached on it"),*GetOwner()->GetName());
	}
	
	if (PressurePlate == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("%s don't have a PressurePlate attached on it"), *GetOwner()->GetName());
	}

	ClosedYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = ClosedYaw;
	OpenedYaw += CurrentYaw;

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(PressurePlate && ActorThatOpens) {

		if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
			OpenDoor(DeltaTime);
			LastTimeDoorOpened = GetWorld()->GetTimeSeconds();
		}
		else if(GetWorld()->GetTimeSeconds() - LastTimeDoorOpened > DoorCloseDelay) {
			CloseDoor(DeltaTime);

		}

	}

}

void UOpenDoor::MoveDoor(float DeltaTime, float TargetYaw, float Speed)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, Speed);

	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = CurrentYaw;


	UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentRotation.ToString());
	GetOwner()->SetActorRotation(CurrentRotation);
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	MoveDoor(DeltaTime, OpenedYaw,OpenDoorSpeed);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	MoveDoor(DeltaTime, ClosedYaw,CloseDoorSpeed);
}

