// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <CastleEscape\PlayerController\GrabbedObjectHandler.h>
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include <CastleEscape\Puzzles\Jigsaw Puzzle\JigsawPiece.h>
#include <CastleEscape\Puzzles\Gems Puzzle\PuzzleGem.h>
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	static FVector GetPlayersWorldPos();
	static FVector GetPlayersReachPos(float Reach);
	static FRotator GetPlayersRotation();
	static FHitResult GetFirstPuzzleSpaceInReach(float Reach);
	static FHitResult GetFirstPhysicsBodyInReach(float Reach);
	static UWorld* World;

private:

	UPROPERTY(EditAnywhere)
	float Reach = 135.f;
	
	UPROPERTY(EditAnywhere)
	float LineThickness = 5.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UGrabbedObjectHandler* GrabbedObjectHandler = nullptr;
	UInputComponent* InputComponent = nullptr;
	AActor* LastFocusedObject = nullptr;

	
	void FindPhysicsHandle();
	void SetupInputComponent();

	void Grab();
	void Release();
	void SearchForFocusedObjectToOutline();
	EGrabbedObjectType GetGrabbedObjectType();
	UGrabbedObject* GetGrabbedObject();
};

UWorld* UGrabber::World = nullptr;
