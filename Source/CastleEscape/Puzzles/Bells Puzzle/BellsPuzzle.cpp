// Copyright Henrique Rachti Assumpção 2020


#include "BellsPuzzle.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UBellsPuzzle::UBellsPuzzle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UBellsPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	/*if(BellsSound)
	{
		UAudioComponent* BellsPuzzleAudioComponent= CreateDefaultSubobject<UAudioComponent>(
         TEXT("BellsPuzzleAudioComponent"));
     
		BellsPuzzleAudioComponent->SetSound(BellsSound);
		BellsPuzzleAudioComponent->Play();
	}*/
}

// Called every frame
void UBellsPuzzle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}