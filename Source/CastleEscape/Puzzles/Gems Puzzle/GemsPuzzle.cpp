// Copyright Henrique Rachti Assumpção 2020


#include "GemsPuzzle.h"
#include "Gem.h"
#include "Components/AudioComponent.h"
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

void UGemsPuzzle::SetLightTorchAudioComponent(USoundBase* LightTorchSound,FSoundAttenuationSettings LightTorchSoundAttenuation)
{
	LightTorchAudioComponent = NewObject<UAudioComponent>(GetOwner());
	LightTorchAudioComponent->SetSound(LightTorchSound);
	LightTorchAudioComponent->AdjustAttenuation(LightTorchSoundAttenuation);
	LightTorchAudioComponent->bIsUISound = true;
}

void UGemsPuzzle::SetPutOutTorchAudioComponent(USoundBase* PutOutTorchSound,FSoundAttenuationSettings PutOutTorchSoundAttenuation)
{
	PutOutTorchAudioComponent = NewObject<UAudioComponent>(GetOwner());
	PutOutTorchAudioComponent->SetSound(PutOutTorchSound);
	PutOutTorchAudioComponent->AdjustAttenuation(PutOutTorchSoundAttenuation);
	PutOutTorchAudioComponent->bIsUISound = true;
}

// Called every frame
void UGemsPuzzle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGemsPuzzle::SetCurrentPuzzlePiecePlaced(ATriggerVolume* GemSpace, UActorComponent* GemPlaced)
{
	for (int i = 0; i < GemSpaces.Num(); i++)
		if (GemSpaces[i].PuzzleSpace == GemSpace)
		{
			GemSpaces[i].CurrentGemPlaced = static_cast<UGem*>(GemPlaced);
			break;
		}

	UpdateTorchFireColor();
	CheckIfItHasBeenSolved();
}

bool UGemsPuzzle::IsPuzzleSpaceAvailable(ATriggerVolume* GemSpaceToCheck)
{
	for (FGemSpace p : GemSpaces)
		if (p.PuzzleSpace == GemSpaceToCheck) {
			return p.bAvailable;
		}

	return false;
}

void UGemsPuzzle::SetPuzzleSpaceAvailability(ATriggerVolume* GemSpace, bool GemSpaceAvailability)
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
	if(!GemResult){ return; }

	if(!IsAllSpacesUnavailable())
	{
		return ;
	}

	UGem* GemResultComponent = GemResult->FindComponentByClass<UGem>();

	if(GemResultComponent)
	{
		const FColor GemResultColor = GemResult->FindComponentByClass<UGem>()->GetGemColor();
		if(CurrentTorchFireColor.R==GemResultColor.R &&CurrentTorchFireColor.G==GemResultColor.G&&CurrentTorchFireColor.B==GemResultColor.B)
		{
			GemResult->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(true);
		}
	}
}

bool UGemsPuzzle::IsAllSpacesUnavailable()
{
	for (int i = 0; i < GemSpaces.Num(); i++)
		if (GemSpaces[i].bAvailable == true) {
			return false;
		}
	return true;
}

bool UGemsPuzzle::IsAllSpacesAvailable()
{
	for (int i = 0; i < GemSpaces.Num(); i++)
		if (GemSpaces[i].bAvailable != true) {
			return false;
		}
	return true;
}

void UGemsPuzzle::UpdateTorchFireColor()
{
	if(!TorchFire){ return; }
	
	if(IsAllSpacesAvailable())
	{		 UE_LOG(LogTemp, Error, TEXT("Deactivate Torch"));

		
		TorchFire->Deactivate();
		LightTorchAudioComponent->Deactivate();
		TorchAmbientSound->GetAudioComponent()->SetActive(false);
		PutOutTorchAudioComponent->Play();
		TorchAmbientSound=nullptr;
		bIsTorchFireActivated=false;
	}
	else
	{
		
		if(!bIsTorchFireActivated)
		{
			UE_LOG(LogTemp, Warning, TEXT("Activate Torch"));
			TorchFire->Activate();
			bIsTorchFireActivated=true;

			if(LightTorchAudioComponent)
			{
				UE_LOG(LogTemp, Error, TEXT("LightTorchAudioComponent Y"));
				LightTorchAudioComponent->Play();				
			}

			if(TorchAmbientSound)
			{
				TorchAmbientSound->GetAudioComponent()->Play();
			}
			
		}
			
		CurrentTorchFireColor.R=0.f;
		CurrentTorchFireColor.G=0.f;
		CurrentTorchFireColor.B=0.f;
	
		for (int i = 0; i < GemSpaces.Num(); i++) {
			if (!GemSpaces[i].bAvailable) {
				FColor GemColor = static_cast<UGem*>(GemSpaces[i].CurrentGemPlaced)->GetGemColor();
				UE_LOG(LogTemp,Warning,TEXT("Mixou com a cor %s"),*GemColor.ToString());
			
				if(CurrentTorchFireColor.R==0.f && CurrentTorchFireColor.G==0.f && CurrentTorchFireColor.B==0.f)
				{
					UE_LOG(LogTemp,Warning,TEXT("UMA COR"));
					CurrentTorchFireColor.R=GemColor.R;
					CurrentTorchFireColor.G=GemColor.G;
					CurrentTorchFireColor.B=GemColor.B;
				}
				else
				{
					UE_LOG(LogTemp,Warning,TEXT("DUAS CORES"));
					CurrentTorchFireColor.R = CurrentTorchFireColor.R*0.5 + GemColor.R*0.5;
					CurrentTorchFireColor.G = CurrentTorchFireColor.G*0.5 + GemColor.G*0.5;
					CurrentTorchFireColor.B = CurrentTorchFireColor.B*0.5 + GemColor.B*0.5;
				}
			}
		}

			UE_LOG(LogTemp,Warning,TEXT("MUDOU A COR"));
			UMaterialInterface* MITorchFire = TorchFire->GetParticleSystemComponent()->GetMaterial(0);
			UMaterialInstanceDynamic* MatTorchFireInstance = TorchFire->GetParticleSystemComponent()->CreateDynamicMaterialInstance(0, MITorchFire);
 
			if(MatTorchFireInstance != nullptr)
			{
				MatTorchFireInstance->SetVectorParameterValue("color1", CurrentTorchFireColor);
			}
	}
}



