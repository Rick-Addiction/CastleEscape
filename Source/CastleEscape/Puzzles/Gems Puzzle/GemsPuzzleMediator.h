// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Particles/Emitter.h"
#include "Components/ActorComponent.h"
#include "GemsPuzzle.h"
#include "Sound/AmbientSound.h"

#include "GemsPuzzleMediator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UGemsPuzzleMediator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGemsPuzzleMediator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Statues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Gems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* PlaceGemSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* LightTorchSound = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USoundBase* PutOutTorchSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundAttenuation* TorchSoundAttenuation;

	UGemsPuzzle* GetGemsPuzzleByPuzzleSpace(ATriggerVolume* PuzzleSpace);

	private:
	UPROPERTY()
	TArray<UGemsPuzzle*> GemStatues;

	void SettingStatues();
	void SettingGems();
		
};
