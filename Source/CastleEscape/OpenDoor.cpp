// Copyright Henrique Rachti Assumpção 2020

#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.h"

#define OUT

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


	if (PressurePlate == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("%s don't have a PressurePlate attached on it"), *GetOwner()->GetName());
	}

	FindAudioComponent();

	ClosedYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = ClosedYaw;
	OpenedYaw += CurrentYaw;	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(PressurePlate) {

		if (GetTotalMassOfActorsOnPlate() > TotalMassNeededToOpen) {
		
			OpenDoor(DeltaTime);
			LastTimeDoorOpened = GetWorld()->GetTimeSeconds();

		}
		else if(GetWorld()->GetTimeSeconds() - LastTimeDoorOpened > DoorCloseDelay) {
			CloseDoor(DeltaTime);
		}

	}
}

void UOpenDoor::FindAudioComponent() {

	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!AudioComponent) {

		UE_LOG(LogTemp, Error, TEXT("AudioComponent isn't attached in %s"), *GetOwner()->GetName())
	}
}


void UOpenDoor::MoveDoor(float DeltaTime, float TargetYaw, float Speed)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, Speed);

	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = CurrentYaw;	

	GetOwner()->SetActorRotation(CurrentRotation);
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	if (AudioComponent) {
		DoorClosed = false;
		if (!DoorOpened) {
			AudioComponent->Play();
			DoorOpened = true;
		}
	}
	
	MoveDoor(DeltaTime, OpenedYaw,OpenDoorSpeed);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{

	if (AudioComponent) {
		DoorOpened = false;
		if (!DoorClosed) {
			AudioComponent->Play();
			DoorClosed = true;
		}
	}

	MoveDoor(DeltaTime, ClosedYaw,CloseDoorSpeed);
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() 
{
	TotalMassOnPlate = 0.0f;

	if (!PressurePlate) { return TotalMassOnPlate; }

	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const auto& Actor : OverlappingActors) {
		Actor->GetName();
		TotalMassOnPlate += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName());
	}

	return TotalMassOnPlate;
}
