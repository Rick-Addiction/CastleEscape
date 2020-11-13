// Copyright Henrique Rachti Assumpção 2020

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "CollisionQueryParams.h"
#include "UObject/Object.h"
#include "Engine/EngineTypes.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"


#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
	World = GetWorld();
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

	if (World) {
		SearchForFocusedObjectToOutline();

		if (PhysicsHandle->GrabbedComponent && GrabbedObjectHandler)
		{
			GrabbedObjectHandler->MoveObject();
		}
	}
}

void UGrabber::Grab() {
	FHitResult HitResult = GetFirstPhysicsBodyInReach(Reach);
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		if (!PhysicsHandle) { return; }

		PhysicsHandle->GrabComponent
		(ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true
		);

		GrabbedObjectHandler = UGrabbedObjectHandler::MAKE(GetGrabbedObjectType(), PhysicsHandle, GetGrabbedObject());
	}
}

void UGrabber::Release() {
	if (!PhysicsHandle) { return; }
	if (!PhysicsHandle->GrabbedComponent) { return; }
	if (!GrabbedObjectHandler) { return; }

	GrabbedObjectHandler->DestroyHandler();
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::SearchForFocusedObjectToOutline() {

	FHitResult HitResult = GetFirstPhysicsBodyInReach(Reach);
	AActor* ActorHit = HitResult.GetActor();

	if (LastFocusedObject != nullptr) {
		LastFocusedObject->FindComponentByClass<UPrimitiveComponent>()->SetRenderCustomDepth(false);
		LastFocusedObject = nullptr;
	}

	if (ActorHit) {
		ActorHit->FindComponentByClass<UPrimitiveComponent>()->SetRenderCustomDepth(true);
		LastFocusedObject = ActorHit;
	}
}

EGrabbedObjectType UGrabber::GetGrabbedObjectType() {

	if (PhysicsHandle->GrabbedComponent->GetOwner()->FindComponentByClass<UJigsawPiece>())
		return EGrabbedObjectType::PUZZLE_PIECE;
	else if (PhysicsHandle->GrabbedComponent->GetOwner()->FindComponentByClass<UPuzzleGem>())
		return EGrabbedObjectType::GEM;
	else
		return EGrabbedObjectType::UNDEFINED;
}

UGrabbedObject* UGrabber::GetGrabbedObject() {

	if (PhysicsHandle->GrabbedComponent->GetOwner()->FindComponentByClass<UJigsawPiece>())
		return PhysicsHandle->GrabbedComponent->GetOwner()->FindComponentByClass<UJigsawPiece>();
	else if (PhysicsHandle->GrabbedComponent->GetOwner()->FindComponentByClass<UPuzzleGem>())
		return PhysicsHandle->GrabbedComponent->GetOwner()->FindComponentByClass<UPuzzleGem>();
	else
		return nullptr;
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach(float Reach){
	FHitResult Hit;


	DrawDebugLine(World, GetPlayersWorldPos(), GetPlayersReachPos(Reach), FColor::Red, false, 0, 0, 5.f);

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, World->GetFirstPlayerController()->GetOwner());

	
	World->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayersWorldPos(),
		GetPlayersReachPos(Reach),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	return Hit;
}

FHitResult UGrabber::GetFirstPuzzleSpaceInReach(float Reach) {

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, World->GetFirstPlayerController()->GetOwner());

	FHitResult Hit;
	World->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayersWorldPos(),
		GetPlayersReachPos(Reach),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_GameTraceChannel1),
		TraceParameters
	);

	return Hit;
}

FVector UGrabber::GetPlayersWorldPos()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	World->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation;
}

FVector UGrabber::GetPlayersReachPos(float Reach)
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	World->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FRotator UGrabber::GetPlayersRotation()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	World->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	return PlayerViewPointRotation;
}
