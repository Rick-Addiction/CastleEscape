// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Particles/Emitter.h"
#include "Components/ActorComponent.h"
#include "GemsPuzzle.h"


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

	UPROPERTY()
	UGemsPuzzle* MainGemsPuzzle;
	
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
	USoundAttenuation* TorchSoundAttenuation = nullptr;

	UPROPERTY(EditAnywhere)
	float GemsPuzzleMovementSpeed = 1.f;

	UPROPERTY(EditAnywhere)
	float ExpectedYStatueLocationWhenPuzzleSolved = 888.f;
	
	UGemsPuzzle* GetGemsPuzzleByPuzzleSpace(ATriggerVolume* PuzzleSpace);

	UPROPERTY(EditAnywhere)
	bool PuzzleCompleted = false;
	
	private:

	UPROPERTY()
	float ExpectedYTorchLocationWhenPuzzleSolved = 0;
	
	
	UPROPERTY()
	TArray<UGemsPuzzle*> GemStatues;
	
	

	UPROPERTY()
	float CurrentYStatuePosition = 0;

	UPROPERTY()
	float CurrentYTorchPosition = 0;

	void SettingStatues();
	void SettingGems();

	void MoveStatue(float DeltaTime);
		
};
