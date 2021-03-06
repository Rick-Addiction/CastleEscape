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

	virtual void Play() override;

	void LightUpTheSphere();
	
	void SetBellsPuzzle(UBellsPuzzle* BellsPuzzle);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedToChangeColor = 1.f;	
	
	protected:
	// Called when the game starts
	virtual void BeginPlay() override;	
	void ChangeSphereColor(float ValueHSV,float DeltaTime);	
	float GetCurrentValueHSV();

	UPROPERTY()
	UBellsPuzzle* BellsPuzzle = nullptr;

	UPROPERTY()
	EInteractableObjectAction CurrentMelodySphereStatus = EInteractableObjectAction::STOPPING;

	UPROPERTY()
	bool ChangeColor;

};
