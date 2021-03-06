// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "PlayerCharacter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UPlayerCharacter : public UObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerCharacter();

	static FVector GetPlayersWorldPos();
	static FVector GetPlayersReachPos(float Reach);
	static FRotator GetPlayersRotation();
	static FHitResult GetFirstPuzzleSpaceInReach(float Reach);
	static FHitResult GetFirstPhysicsBodyInReach(float Reach);
	static UPhysicsHandleComponent* GetPhysicsHandle();
	static UInputComponent* GetInputComponent();

	static UWorld* World;


};
UWorld* UPlayerCharacter::World = nullptr;