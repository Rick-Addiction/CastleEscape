// Copyright Henrique Rachti Assumpção 2020


#include "Gem.h"
#include "Components/AudioComponent.h"
#include "GemsPuzzle.h"

// Sets default values for this component's properties
UGem::UGem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts	
void UGem::BeginPlay()
{
	Super::BeginPlay();

	UPrimitiveComponent* GrabbedObjectPrimitiveComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	GrabbedObjectPrimitiveComponent->GetBodyInstance()->bLockXTranslation = true;
	GrabbedObjectPrimitiveComponent->GetBodyInstance()->bLockYTranslation= true;
	GrabbedObjectPrimitiveComponent->GetBodyInstance()->bLockZTranslation= false;
	GrabbedObjectPrimitiveComponent->GetBodyInstance()->bLockXRotation = false;
	GrabbedObjectPrimitiveComponent->GetBodyInstance()->bLockYRotation= false;
	GrabbedObjectPrimitiveComponent->GetBodyInstance()->bLockZRotation= false;
	GrabbedObjectPrimitiveComponent->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);
	
}

void UGem::SetPlaceGemAudioComponent(USoundBase* PlaceGemSound)
{
	PlaceGemAudioComponent = NewObject<UAudioComponent>(GetOwner());
	PlaceGemAudioComponent->SetSound(PlaceGemSound);
}



// Called every frame
void UGem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	
}

void UGem::PlacePuzzleObjectInPuzzleSpace() {
	GetOwner()->SetActorLocation(PuzzleSpace->GetActorLocation());
	FRotator NewGrabbedObjectRotation = PuzzleSpace->GetActorRotation();
	NewGrabbedObjectRotation.Roll -= 90;	
	GetOwner()->SetActorRotation(NewGrabbedObjectRotation);

	
	//TODO Faz sentido essas chamadas do Puzzle?
	static_cast<UGemsPuzzle*>(Puzzle)->SetPuzzleSpaceAvailability(PuzzleSpace, false);
	static_cast<UGemsPuzzle*>(Puzzle)->SetCurrentPuzzlePiecePlaced(PuzzleSpace, this);
	
	
	LastPuzzleSpaceOccupied = PuzzleSpace;
	UPrimitiveComponent* GemPrimitiveComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	GemPrimitiveComponent->SetSimulatePhysics(false);

	if (PlaceGemAudioComponent) {
		PlaceGemAudioComponent->Play();
	}
}

void UGem::RemovePuzzleObjectFromPuzzleSpace() {
	if (LastPuzzleSpaceOccupied != nullptr) {
		
		static_cast<UGemsPuzzle*>(Puzzle)->SetPuzzleSpaceAvailability(LastPuzzleSpaceOccupied, true);
		static_cast<UGemsPuzzle*>(Puzzle)->SetCurrentPuzzlePiecePlaced(LastPuzzleSpaceOccupied, nullptr);
		SetPuzzle(nullptr);
		LastPuzzleSpaceOccupied = nullptr;
	}

	GetOwner()->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(true);

	if (PlaceGemAudioComponent) {
		PlaceGemAudioComponent->Play();
	}
}

FColor UGem::GetGemColor()
{
	UMaterialInstanceDynamic* MIGem = UMaterialInstanceDynamic::Create(
                    GetOwner()->FindComponentByClass<UPrimitiveComponent>()->GetMaterial(0),
                    this);

	FLinearColor GemColor;
	MIGem->GetVectorParameterValue(FName(TEXT("Gem_Depth_01_Color")),OUT GemColor, false);

	return GemColor.ToFColor(true);	
}

void UGem::SetPuzzleManager(UGemsPuzzleMediator* PuzzleManagerToSet)
{
	PuzzleManager = PuzzleManagerToSet;	
}

UGemsPuzzleMediator* UGem::GetPuzzleManager() const
{
	return PuzzleManager;	
}
