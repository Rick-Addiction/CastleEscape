// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
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
	
	FHitResult GetFirstPuzzleSpaceInReach();
	bool IsPuzzlePiece();

private:

	UPROPERTY(EditAnywhere)
	float Reach = 100.f;
	
	UPROPERTY(EditAnywhere)
	float LineThickness = 5.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	AActor* LastFocusedObject = nullptr;

	void Grab();
	void Release();
	void Spin();
	void FindPhysicsHandle();
	void SetupInputComponent();
	void SearchForFocusedObjectToOutline();
	const FHitResult GetFirstPhysicsBodyInReach();
	FRotator GetCurrentGrabbedObjectRotation();
	FVector GetPlayersWorldPos();
	FVector GetPlayersReachPos();
	FRotator GetPlayersRotation();
	void MoveObject();
	void UpdatePuzzleSpaceForPuzzlePiece();

	

	



};
