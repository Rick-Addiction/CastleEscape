// Copyright Henrique Rachti Assumpção 2020


#include "GemsPuzzle.h"

#include "Gem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
UGemsPuzzle::UGemsPuzzle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGemsPuzzle::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGemsPuzzle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGemsPuzzle::SetCurrentPuzzlePiecePlaced(AActor* GemSpace, AActor* GemPlaced)
{
	for (int i = 0; i < GemSpaces.Num(); i++)
		if (GemSpaces[i].PuzzleSpace == GemSpace)
		{
			GemSpaces[i].CurrentGemPlaced = GemPlaced;
			UpdateTorchFireColor();
			break;
		}
}

bool UGemsPuzzle::CheckIfPuzzleSpaceIsAvailable(AActor* GemSpaceToCheck)
{
	for (FGemSpace p : GemSpaces)
		if (p.PuzzleSpace == GemSpaceToCheck) {
			return p.bAvailable;
		}

	return false;
}

void UGemsPuzzle::SetPuzzleSpaceAvailability(AActor* GemSpace, bool GemSpaceAvailability)
{
	for (int i = 0; i < GemSpaces.Num(); i++) {
		if (GemSpaces[i].PuzzleSpace == GemSpace) {
			GemSpaces[i].bAvailable = GemSpaceAvailability;
			break;
		}
	}	
}

void UGemsPuzzle::CheckIfItHasBeenSolved()
{


	
}

bool UGemsPuzzle::CheckIfAllSpacesHasAPuzzle()
{
	for (int i = 0; i < GemSpaces.Num(); i++)
		if (GemSpaces[i].bAvailable == true) {
			return false;
		}

	return true;
}

void UGemsPuzzle::UpdateTorchFireColor()
{
	FLinearColor TorchFireColor;
	TorchFireColor.R=0.f;
	TorchFireColor.G=0.f;
	TorchFireColor.B=0.f;
	
	for (int i = 0; i < GemSpaces.Num(); i++) {
		if (!GemSpaces[i].bAvailable) {
			FLinearColor GemColor = GemSpaces[i].CurrentGemPlaced->FindComponentByClass<UGem>()->GetGemColor();
			
			if(TorchFireColor.R==0.f && TorchFireColor.G==0.f && TorchFireColor.B==0.f)
			{
				TorchFireColor.R=GemColor.R;
				TorchFireColor.G=GemColor.G;
				TorchFireColor.B=GemColor.B;
			}
			else
			{
				TorchFireColor.R = TorchFireColor.R*0.5 + GemColor.R*0.5;
				TorchFireColor.G = TorchFireColor.G*0.5 + GemColor.G*0.5;
				TorchFireColor.B = TorchFireColor.B*0.5 + GemColor.B*0.5;
			}
		}
	}

	if(TorchFire)
	{
		UMaterialInterface* MITorchFire = TorchFire->GetParticleSystemComponent()->GetMaterial(0);
		UMaterialInstanceDynamic* MatTorchFireInstance = TorchFire->GetParticleSystemComponent()->CreateDynamicMaterialInstance(0, MITorchFire);
 
		if(MatTorchFireInstance != nullptr)
		{
			FLinearColor verificacao;
			MatTorchFireInstance->GetVectorParameterValue(FName(TEXT("color1")),verificacao);
			MatTorchFireInstance->SetVectorParameterValue("color1", TorchFireColor);
			FLinearColor verificacao2;
			MatTorchFireInstance->GetVectorParameterValue(FName(TEXT("color1")),verificacao2);
		}
	}

	
}



