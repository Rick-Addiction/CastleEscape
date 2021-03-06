// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"

#include "Pipe.h"
#include "PlayerController/InteractableObject.h"

#include "PipeValve.generated.h"

UENUM(BlueprintType)
enum EPipeValveState
{
	DISABLED = 0 UMETA(DisplayName = "DISABLED"),
    ENABLED UMETA(DisplayName = "ENABLED")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UPipeValve : public UInteractableObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPipeValve();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Play() override;
	void ChangePipesValveState();
	void AddPipeComponentThatValveControls(UPipe* PipeComponentThatValveControls);
	void TurnValve(float DeltaTime);
	bool IsEnabled() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ValveSpeed = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DelayToChangePipeState = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PipeThatComesTheFlow = 0.5f;

	


private:

	TEnumAsByte<EInteractableObjectAction> PipeValveAction = EInteractableObjectAction::STOPPING;
	
	TEnumAsByte<EPipeValveState> PipeValveState = EPipeValveState::DISABLED;

	UPROPERTY()
	TSet<UPipe*> PipeComponentsThatValveControlsTheFlow;
	
};
