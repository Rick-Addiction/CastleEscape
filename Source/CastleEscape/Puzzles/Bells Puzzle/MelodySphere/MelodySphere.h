// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"


#include "PlayerController/InteractableObject.h"
#include "Puzzles/Bells Puzzle/BellsPuzzle.h"

#include "MelodySphere.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UMelodySphere : public UInteractableObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMelodySphere();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PlayMelody();

	void LightUpTheSphere();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* WallWhereTheSphereIsPlaced = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedToChangeColor = 1.f;
	
	protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	UBellsPuzzle* BellsPuzzle = nullptr;

	EInteractableObjectStats CurrentMelodySphereStatus = EInteractableObjectStats::NONE;

	void ChangeSphereColor(float ValueHSV,float DeltaTime);

	bool ChangeColor;

	float GetCurrentValueHSV();
};
