// Copyright Henrique Rachti Assumpção 2020

#include "PlayerCharacter.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "CollisionQueryParams.h"
#include "Engine/EngineTypes.h"

#define OUT

// Sets default values for this component's properties
UPlayerCharacter::UPlayerCharacter()
{
	
}

FHitResult UPlayerCharacter::GetFirstPhysicsBodyInReach(float Reach){
	FHitResult Hit;
	DrawDebugLine(World, GetPlayersWorldPos(), GetPlayersReachPos(Reach), FColor::Red, false, 0, 0, 10.f);
	
	
	const FCollisionQueryParams TraceParameters(FName(TEXT("")), false, World->GetFirstPlayerController()->GetOwner());

	if(World)
	World->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayersWorldPos(),
		GetPlayersReachPos(Reach),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	return Hit;
}

FHitResult UPlayerCharacter::GetFirstPuzzleSpaceInReach(float Reach) {

	const FCollisionQueryParams TraceParameters(FName(TEXT("")), false, World->GetFirstPlayerController()->GetOwner());

	FHitResult Hit;

	if(World)
	World->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayersWorldPos(),
		GetPlayersReachPos(Reach),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_GameTraceChannel1),
		TraceParameters
	);

	return Hit;
}

FVector UPlayerCharacter::GetPlayersWorldPos()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	if(World)
	World->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation;
}

FVector UPlayerCharacter::GetPlayersReachPos(float Reach)
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	if(World)
	World->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FRotator UPlayerCharacter::GetPlayersRotation()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	if(World)
	World->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	return PlayerViewPointRotation;
}

UPhysicsHandleComponent* UPlayerCharacter::GetPhysicsHandle()
{
	if(!World){return nullptr;}
	if(!World->GetFirstPlayerController()->GetPawn())
	{
		UE_LOG(LogTemp,Error, TEXT("There isn't a FirstPlayerController"))
		return nullptr;
	}
	
	UPhysicsHandleComponent* PhysicsHandleComponent = World->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UPhysicsHandleComponent>();

	if(PhysicsHandleComponent)
	{
		return PhysicsHandleComponent;
	}
	else
	{
		UE_LOG(LogTemp,Error, TEXT("There isn't a PhysicsHandleComponent attached to the Player Character"))
		return nullptr;
	}
	
}

UInputComponent* UPlayerCharacter::GetInputComponent()
{
	if(!World){return nullptr;}
	if(World && !World->GetFirstPlayerController())
	{
		UE_LOG(LogTemp,Error, TEXT("There isn't a FirstPlayerController"))
		return nullptr;
	}
	
	UInputComponent* InputComponent = World->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UInputComponent>();
	
	if(InputComponent)
	{
		return InputComponent;
	}
	else
	{
		UE_LOG(LogTemp,Error, TEXT("There isn't a InputComponent attached to the Player Character"))
		return nullptr;
	}
}
