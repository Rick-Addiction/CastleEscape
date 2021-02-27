// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Pipe.generated.h"

UENUM(BlueprintType)
enum EPipeCurrentState
{
	FLOWING_WATER UMETA(DisplayName = "FLOWING_WATER"),
    FULL_OF_WATER UMETA(DisplayName = "FULL_OF_WATER"),
    DRAINING_OUT_WATER UMETA(DisplayName = "DRAINING_WATER"),
	EMPTY_OF_WATER UMETA(DisplayName = "EMPTY_OF_WATER"),
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UPipe : public UActorComponent
{
	GENERATED_BODY()


	protected:	
	void CreateDynamicLiquidMaterial();
	USceneComponent* GetLiquidSceneComponent();	
	UStaticMeshComponent* GetLiquidStaticMeshComponent();
	
	public:
	virtual void FlowWater(float DeltaTime){ check(0 && "You must override this"); };
	virtual void DrainOutWater(float DeltaTime){ check(0 && "You must override this"); };
	virtual void CheckAndStartNextPipe(){ check(0 && "You must override this"); };
	virtual bool IsPipeFull(){ check(0 && "You must override this"); return 0;};
	virtual bool IsPipeEmpty(){ check(0 && "You must override this"); return 0;};
	virtual void ChangePipeToDrainOutMode(){ check(0 && "You must override this"); };
	virtual void ChangePipeToFlowingMode(){ check(0 && "You must override this"); };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EPipeCurrentState> CurrentState = EPipeCurrentState::EMPTY_OF_WATER;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaterSpeed = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* NextPipe = nullptr;
};