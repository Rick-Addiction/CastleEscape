// Copyright Henrique Rachti Assumpção 2020

#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "CollisionQueryParams.h"
#include "UObject/Object.h"
#include "Engine/EngineTypes.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include <CastleEscape\PuzzlePiece.h>
#include "Grabber.h"


#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}


void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab is pressed"))

	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		if (!PhysicsHandle) { return; }

		if (ActorHit->FindComponentByClass<UPuzzlePiece>() !=nullptr) {
			UE_LOG(LogTemp, Error, TEXT("A UPuzzlePiece has been grabbed"))
			ActorHit->FindComponentByClass<UPuzzlePiece>()->SetGrabbed(true);
		}

		PhysicsHandle->GrabComponent
		(ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true
		);
	}
}

void UGrabber::Release() {
	if (!PhysicsHandle) { return; }

	if (!PhysicsHandle->GrabbedComponent) { return; }

	if (PhysicsHandle->GrabbedComponent->GetOwner()->FindComponentByClass<UPuzzlePiece>()) {
		UE_LOG(LogTemp, Error, TEXT("A UPuzzlePiece has been released"))
		PhysicsHandle->GrabbedComponent->GetOwner()->FindComponentByClass<UPuzzlePiece>()->SetGrabbed(false);
	}

	UE_LOG(LogTemp, Warning, TEXT("Grab is released"))

	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandle() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandle){

		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle isn't attached in %s"), *GetOwner()->GetName())
	}
}

void UGrabber::SetupInputComponent() {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {

		UE_LOG(LogTemp, Error, TEXT("InputComponent isn't attached in %s"), *GetOwner()->GetName())
	}

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle) { return; }

	if (PhysicsHandle->GrabbedComponent)
	{

		if (PhysicsHandle->GrabbedComponent->GetOwner()->FindComponentByClass<UPuzzlePiece>()) {
			UPuzzlePiece* component = PhysicsHandle->GrabbedComponent->GetOwner()->FindComponentByClass<UPuzzlePiece>();
			if (!component->IsSet()) {
				PhysicsHandle->SetTargetLocation(GetPlayersReachPos());
			}

		}
		else {
			PhysicsHandle->SetTargetLocation(GetPlayersReachPos());
		}

		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

		PhysicsHandle->SetTargetRotation(PlayerViewPointRotation);
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach(){

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayersWorldPos(),
		GetPlayersReachPos(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	return Hit;

}

FVector UGrabber::GetPlayersWorldPos()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation;
}


FVector UGrabber::GetPlayersReachPos()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}


