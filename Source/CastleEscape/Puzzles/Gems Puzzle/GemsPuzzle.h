// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Particles/Emitter.h"
#include "Engine/TriggerVolume.h"
#include "CastleEscape/Puzzles/Puzzle.h"
#include "GemsPuzzle.generated.h"

class AAmbientSound;
USTRUCT(BlueprintType)
struct FGemSpace
{
    GENERATED_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ATriggerVolume* PuzzleSpace;

	UPROPERTY()
    UActorComponent* CurrentGemPlaced = nullptr;

    bool bAvailable = true;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UGemsPuzzle : public UPuzzle
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGemsPuzzle();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetCurrentPuzzlePiecePlaced(ATriggerVolume* PuzzleSpace, UActorComponent* PuzzlePiecePlaced) override;

	virtual bool IsPuzzleSpaceAvailable(ATriggerVolume* GemSpaceToCheck) override;

	virtual void SetPuzzleSpaceAvailability(ATriggerVolume* GemSpace, bool GemSpaceAvailability) override;

	virtual void CheckIfItHasBeenSolved() override;

	virtual bool IsAllSpacesUnavailable() override;

	virtual bool IsAllSpacesAvailable() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGemSpace> GemSpaces;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AEmitter* TorchFire = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AAmbientSound* TorchAmbientSound = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance* MaterialResult = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* GemExpectedWhenPuzzleSolved = nullptr;

	FColor CurrentTorchFireColor;

	UPROPERTY()
	bool bIsTorchFireActivated = false;

	UPROPERTY(EditAnywhere)
	bool bIsPuzzleSolved = false;

	UPROPERTY()
	UAudioComponent* LightTorchAudioComponent = nullptr;

	UPROPERTY()
	UAudioComponent* PutOutTorchAudioComponent = nullptr;	

	int GetNumberOfGemsPlaced();
	
	void SetLightTorchAudioComponent(USoundBase* LightTorchSound,FSoundAttenuationSettings LightTorchSoundAttenuation);

	void SetPutOutTorchAudioComponent(USoundBase* PutOutTorchSound,FSoundAttenuationSettings PutOutTorchSoundAttenuation);

	void UpdateTorchFireColor();

	private:


	void SettingExpectedColorToSolvePuzzle();

	UPROPERTY()
	FColor ExpectedColorToSolvePuzzle;
};
