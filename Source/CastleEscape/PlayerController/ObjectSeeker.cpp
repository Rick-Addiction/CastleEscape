// Copyright Henrique Rachti Assumpção 2020

#include "ObjectSeeker.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.h"
#include "PlayerCharacter.h"
#include "UObject/Object.h"
#include "Engine/EngineTypes.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "ObjectHandler/GrabbableObjectHandler.h"
#include "ObjectHandler/InteractableObjectHandler.h"

#define OUT

// Sets default values for this component's properties
UObjectSeeker::UObjectSeeker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UObjectSeeker::BeginPlay()
{
	Super::BeginPlay();

	UPlayerCharacter::World = GetWorld();

	SetupInputComponent();
}

void UObjectSeeker::SetupInputComponent() {
	UInputComponent* InputComponent = UPlayerCharacter::GetInputComponent();

	if (InputComponent) {
		InputComponent->BindAction("Seek", IE_Pressed, this, &UObjectSeeker::Seek);
		InputComponent->BindAction("Seek", IE_Released, this, &UObjectSeeker::RestartSeeking);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("InputComponent isn't attached in %s"), *GetOwner()->GetName())
	}
}


void UObjectSeeker::Seek()
{
	
	const FHitResult HitResult = UPlayerCharacter::GetFirstPhysicsBodyInReach(Reach);
	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Error, TEXT("ActorHit"))
			if(ActorHit->FindComponentByClass<UGrabbableObject>()){
				if(!UPlayerCharacter::GetPhysicsHandle()){return;}
				
				ObjectHandler = UGrabbableObjectHandler::Make(ActorHit);
			}
			else if(ActorHit->FindComponentByClass<UInteractableObject>())
			{
				
				ObjectHandler = UInteractableObjectHandler::Make(ActorHit);
			}
			else
			{
				ObjectHandler = nullptr;
			}

			UInputComponent* InputComponent = UPlayerCharacter::GetInputComponent();			
			if (ObjectHandler && InputComponent) {
				InputComponent->RemoveActionBinding("Seek", IE_Pressed);
			}	

	}
}

void UObjectSeeker::RestartSeeking()
{
	UInputComponent* InputComponent = UPlayerCharacter::GetInputComponent();
	if (ObjectHandler && InputComponent)
	{
		InputComponent->BindAction("Seek", IE_Pressed, this, &UObjectSeeker::Seek);
		ObjectHandler = nullptr;
	}
}

// Called every frame
void UObjectSeeker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!UPlayerCharacter::GetPhysicsHandle()) { return; }
	if(UPlayerCharacter::World)
	{
		SearchForFocusedObjectToOutline();

		if (ObjectHandler)
		{
			ObjectHandler->Handle();
		}
	}

}

void UObjectSeeker::SearchForFocusedObjectToOutline() {

	const FHitResult HitResult = UPlayerCharacter::GetFirstPhysicsBodyInReach(Reach);
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