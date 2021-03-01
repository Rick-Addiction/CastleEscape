// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Puzzles/Pipes Puzzle/Pipe.h"

#include "StraightPipe.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UStraightPipe : public UPipe
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStraightPipe();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void ManageFlowWater(float DeltaTime) override;
	virtual void ManageDrainOutWater(float DeltaTime) override;
	virtual void ChangePipeToDrainOutState() override;
	virtual void ChangePipeToFlowingState() override;
	
	virtual void CheckAndStartNextPipe() override;
	virtual void SettingNextPipe() override;
	virtual void SettingValveThatControlsThePipe() override;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void FlowWater(float DeltaTime) override;
	virtual void DrainOutWater(float DeltaTime) override;
	
	virtual void SchedulePipeToDrainOutState() override;
	virtual void SchedulePipeToFlowWaterState() override;
	virtual bool IsPipeFull() override;
	virtual bool IsPipeEmpty() override;
	virtual bool IsPipeFlowEnable() override;
		
};
