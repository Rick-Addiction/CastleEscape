// Copyright Henrique Rachti Assumpção 2020


#include "GemsPuzzle.h"
#include <cmath> 
#include "Gem.h"
#include "Components/AudioComponent.h"
#include "Sound/AmbientSound.h"
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

	SettingExpectedColorToSolvePuzzle();
}


void UGemsPuzzle::SettingExpectedColorToSolvePuzzle()
{
	FLinearColor GemColor;
	MaterialResult->GetVectorParameterValue(FName(TEXT("Gem_Depth_01_Color")),OUT GemColor, false);

	ExpectedColorToSolvePuzzle = GemColor.ToFColor(true);
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

	if(!bIsPuzzleSolved)
	{
		UpdateTorchFireColor();
		CheckIfItHasBeenSolved();
	}
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
	if(!MaterialResult){ return; }

	if(!IsAllSpacesUnavailable())
	{
		return ;
	}

	UE_LOG(LogTemp,Warning,TEXT("CurrentTorchFireColor: %s  | GemExpectedWhenPuzzleSolved: %s"),*CurrentTorchFireColor.ToString(),*ExpectedColorToSolvePuzzle.ToString());

		if(CurrentTorchFireColor.R==ExpectedColorToSolvePuzzle.R && CurrentTorchFireColor.G==ExpectedColorToSolvePuzzle.G&& CurrentTorchFireColor.B==ExpectedColorToSolvePuzzle.B)
		{
			if(GemExpectedWhenPuzzleSolved && GemExpectedWhenPuzzleSolved->FindComponentByClass<UGem>())
			{
				UE_LOG(LogTemp,Warning,TEXT("ACERTOU"));
				
				GemExpectedWhenPuzzleSolved->FindComponentByClass<USceneComponent>()->SetMobility(EComponentMobility::Movable);
			
				GemExpectedWhenPuzzleSolved->FindComponentByClass<UPrimitiveComponent>()->GetBodyInstance()->bLockXTranslation = false;
				GemExpectedWhenPuzzleSolved->FindComponentByClass<UPrimitiveComponent>()->GetBodyInstance()->bLockYTranslation= false;
				GemExpectedWhenPuzzleSolved->FindComponentByClass<UPrimitiveComponent>()->GetBodyInstance()->bLockZTranslation= false;
				GemExpectedWhenPuzzleSolved->FindComponentByClass<UPrimitiveComponent>()->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
				GemExpectedWhenPuzzleSolved->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(true);
			}

			UE_LOG(LogTemp,Warning,TEXT("SOLVED"));
			
			bIsPuzzleSolved = true;
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("ERROU"));
			
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

int UGemsPuzzle::GetNumberOfGemsPlaced()
{
	int NumGems = 0;
	for (int i = 0; i < GemSpaces.Num(); i++)
	{
		if (!GemSpaces[i].bAvailable)
		{
			NumGems++;
		}
	}
return NumGems;
	
}

void UGemsPuzzle::UpdateTorchFireColor()
{
	if(!TorchFire){ return; }
	
	if(IsAllSpacesAvailable())
	{		 UE_LOG(LogTemp, Error, TEXT("Deactivate Torchhh"));

		
		TorchFire->Deactivate();
		LightTorchAudioComponent->Deactivate();
		TorchAmbientSound->GetAudioComponent()->SetActive(false);
		PutOutTorchAudioComponent->Play();
		bIsTorchFireActivated=false;
	}
	else
	{
		
		if(!bIsTorchFireActivated)
		{
			UE_LOG(LogTemp, Warning, TEXT("Activate Torchhh"));
			TorchFire->Activate();
			bIsTorchFireActivated=true;

			if(LightTorchAudioComponent)
			{
				UE_LOG(LogTemp, Error, TEXT("LightTorchAudioComponent YY"));
				LightTorchAudioComponent->Play();				
			}

			if(TorchAmbientSound)
			{
				TorchAmbientSound->GetAudioComponent()->Play();
			}
			
		}
			
		float RedColor =0.f;
		float GreenColor=0.f;
		float BlueColor=0.f;

		const float FractionColor  = 1.f/static_cast<float>(GetNumberOfGemsPlaced());
		
		for (int i = 0; i < GemSpaces.Num(); i++) {
			if (!GemSpaces[i].bAvailable) {
				FColor GemColor = static_cast<UGem*>(GemSpaces[i].CurrentGemPlaced)->GetGemColor();
				UE_LOG(LogTemp,Warning,TEXT("Mixou com a corrrrr %f | %d"),FractionColor,GetNumberOfGemsPlaced());
							
					RedColor+= static_cast<float>(GemColor.R) * FractionColor;
					GreenColor+= static_cast<float>(GemColor.G) * FractionColor;
					BlueColor+= static_cast<float>(GemColor.B) * FractionColor;
				
			}
		}

		CurrentTorchFireColor.R=round(RedColor);
		CurrentTorchFireColor.G=round(GreenColor);
		CurrentTorchFireColor.B=round(BlueColor);

			UE_LOG(LogTemp,Warning,TEXT("MUDOU A COR"));
			UMaterialInterface* MITorchFire = TorchFire->GetParticleSystemComponent()->GetMaterial(0);
			UMaterialInstanceDynamic* MatTorchFireInstance = TorchFire->GetParticleSystemComponent()->CreateDynamicMaterialInstance(0, MITorchFire);
 
			if(MatTorchFireInstance != nullptr)
			{
				MatTorchFireInstance->SetVectorParameterValue("color1", CurrentTorchFireColor);
			}
	}
}



