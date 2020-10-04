// Copyright Henrique Rachti Assumpção 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
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

	rotationWhileClosed = GetOwner()->GetActorRotation().Add(0, 90, 0);
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator currentRotation = GetOwner()->GetActorRotation();
	currentRotation.Yaw = FMath::FInterpTo(currentRotation.Yaw, rotationWhileClosed.Yaw, DeltaTime,2);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *currentRotation.ToString());
	GetOwner()->SetActorRotation(currentRotation);

}

