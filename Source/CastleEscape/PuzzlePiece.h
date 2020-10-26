// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "UObject/Object.h"
#include "PuzzlePiece.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UPuzzlePiece : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzlePiece();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool IsSet();

	void SetGrabbed(bool isGrabbed);

	void SetPuzzleSpace(AActor* PuzzleSpaceFound);
		
private:

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PuzzleSpace = nullptr;

	UPROPERTY(EditAnywhere)
	bool bIsSet = false;

	bool IsGrabbed = false;
};
