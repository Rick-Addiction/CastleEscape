// Copyright Henrique Rachti Assumpção 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
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

	ClosedYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = ClosedYaw;
	OpenedYaw += CurrentYaw;

	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (ActorThatOpen == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("The value of ActorThatOpen is null"));
	}
	else if (PressurePlate == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("The value of PressurePlate is null"));
	}
	else {

		if (PressurePlate->IsOverlappingActor(ActorThatOpen)) {
			OpenDoor(DeltaTime);
		}
		else {
			CloseDoor(DeltaTime);

		}

	}

}

void UOpenDoor::MoveDoor(float DeltaTime, float TargetYaw)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2);

	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = CurrentYaw;


	UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentRotation.ToString());
	GetOwner()->SetActorRotation(CurrentRotation);
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	MoveDoor(DeltaTime, OpenedYaw);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	MoveDoor(DeltaTime, ClosedYaw);
}

