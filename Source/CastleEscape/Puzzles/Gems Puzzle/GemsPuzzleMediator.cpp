// Copyright Henrique Rachti Assumpção 2020


#include "GemsPuzzleMediator.h"

#include "Gem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
UGemsPuzzleMediator::UGemsPuzzleMediator()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}


// Called when the game starts
void UGemsPuzzleMediator::BeginPlay()
{
    Super::BeginPlay();

    SettingStatues();
    SettingGems();
}

void UGemsPuzzleMediator::SettingStatues()
{
    for (int i = 0; i < Statues.Num(); i++)
    {
        if (Statues[i]->FindComponentByClass<UGemsPuzzle>())
        {
            GemStatues.Add(Statues[i]->FindComponentByClass<UGemsPuzzle>());

            if(LightTorchSound)
            {
                Statues[i]->FindComponentByClass<UGemsPuzzle>()->SetLightTorchAudioComponent(LightTorchSound,TorchSoundAttenuation->Attenuation);
            }
            if(PutOutTorchSound)
            {
                Statues[i]->FindComponentByClass<UGemsPuzzle>()->SetPutOutTorchAudioComponent(PutOutTorchSound,TorchSoundAttenuation->Attenuation);
            }         
        }
    }
}

void UGemsPuzzleMediator::SettingGems()
{
    for (int i = 0; i < Gems.Num(); i++)
    {
        if (Gems[i]->FindComponentByClass<UGem>())
        {
            Gems[i]->FindComponentByClass<UGem>()->SetPuzzleManager(this);
            
            if(PlaceGemSound)
            {
                Gems[i]->FindComponentByClass<UGem>()->SetPlaceGemAudioComponent(PlaceGemSound);
            }
        }
    }
}

// Called every frame
void UGemsPuzzleMediator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

UGemsPuzzle* UGemsPuzzleMediator::GetGemsPuzzleByPuzzleSpace(ATriggerVolume* PuzzleSpaceToSet)
{
    if (!PuzzleSpaceToSet) { return nullptr; }

    for (int i = 0; i < GemStatues.Num(); i++)
    {
        for (int j = 0; j < GemStatues[i]->GemSpaces.Num(); j++)
        {
            if (GemStatues[i]->GemSpaces[j].PuzzleSpace == PuzzleSpaceToSet)
            {
                return GemStatues[i];
            }
        }
    }

    return nullptr;
}
