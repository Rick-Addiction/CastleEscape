// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Pipe.generated.h"

class UPipeValve;
class UPipe;
UENUM(BlueprintType)
enum EPipeCurrentState
{
	SCHEDULED_TO_FLOW_WATER UMETA(DisplayName = "SCHEDULED_TO_FLOW_WATER"),
	FLOWING_WATER UMETA(DisplayName = "FLOWING_WATER"),
    FULL_OF_WATER UMETA(DisplayName = "FULL_OF_WATER"),
	SCHEDULED_TO_DRAIN_OUT_WATER UMETA(DisplayName = "SCHEDULED_TO_DRAIN_OUT_WATER"),
    DRAINING_OUT_WATER UMETA(DisplayName = "DRAINING_WATER"),
	EMPTY_OF_WATER UMETA(DisplayName = "EMPTY_OF_WATER"),
};

USTRUCT(BlueprintType)
struct FSourcesOfWater
{
	GENERATED_BODY();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Pipe = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* ValveThatEnableTheFlow = nullptr;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UPipe : public UActorComponent
{
	GENERATED_BODY()

	protected:	
	void CreateDynamicLiquidMaterial();
	USceneComponent* GetLiquidSceneComponent();	
	UStaticMeshComponent* GetLiquidStaticMeshComponent();	

	virtual void ChangePipeToFlowingState(){ check(0 && "You must override this"); };
	virtual void ManageScheduledFlowWater(float DeltaTime){ check(0 && "You must override this"); };
	virtual void ManageFlowWater(float DeltaTime){ check(0 && "You must override this"); };	

	virtual void ChangePipeToDrainOutState(){ check(0 && "You must override this"); };
	virtual void ManageScheduledDrainOutWater(float DeltaTime){ check(0 && "You must override this"); };
	virtual void ManageDrainOutWater(float DeltaTime){ check(0 && "You must override this"); };
	

	virtual void SettingNextPipes(){ check(0 && "You must override this"); };
	virtual void SettingValveThatControlsThePipe(){ check(0 && "You must override this"); };

	virtual void CheckAndFlowNextPipe(){ check(0 && "You must override this"); };
	virtual void CheckAndDrainOutNextPipe(){ check(0 && "You must override this"); };

	virtual void HideWater(){ check(0 && "You must override this"); };
	virtual void ExposeWater(){ check(0 && "You must override this"); };
	
	public:
	virtual void FlowWater(float DeltaTime){ check(0 && "You must override this"); };
	virtual void DrainOutWater(float DeltaTime){ check(0 && "You must override this"); };

	virtual bool IsScheduledToDrainOutWater(){ check(0 && "You must override this"); return 0;};
	
	virtual bool IsPipeFull(){ check(0 && "You must override this"); return 0;};
	virtual bool IsPipeEmpty(){ check(0 && "You must override this"); return 0;};
	
	virtual bool IsPipeAbleToFlowWater(){ check(0 && "You must override this"); return 0;};
	virtual bool IsPipeDrainOutAble(){ check(0 && "You must override this"); return 0;};
	
	virtual void SchedulePipeToDrainOutState(){ check(0 && "You must override this"); };
	virtual void SchedulePipeToFlowWaterState(){ check(0 && "You must override this"); };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EPipeCurrentState> CurrentState = EMPTY_OF_WATER;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaterSpeed = 0.5f;

    UPROPERTY()
	TArray<UPipe*> NextPipes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSourcesOfWater> SourcesOfWater;
};