// Copyright Henrique Rachti Assumpção 2020

#pragma once

#include "CoreMinimal.h"
#include "CastleEscape/PlayerController/GrabbableObject.h"
#include "JigsawPiece.generated.h"

UENUM(BlueprintType)
enum EJigsawPieceRotationRoll
{
	TOP = 0 UMETA(DisplayName = "TOP"),
    LEFT UMETA(DisplayName = "LEFT"),
    BOTTOM UMETA(DisplayName = "BOTTOM"),
    RIGHT UMETA(DisplayName = "RIGHT")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UJigsawPiece : public UGrabbableObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJigsawPiece();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	float GetNextRotationRoll();
	float GetCurrentRotationRoll() const;

	void SetPlaceJigsawPieceAudioComponent(USoundBase* PlaceJigsawPieceSound);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EJigsawPieceRotationRoll> CurrentJigsawPieceRotation = EJigsawPieceRotationRoll::TOP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATriggerVolume* JigsawPieceSpaceExpected = nullptr;
	
private:

	virtual void PlacePuzzleObjectInPuzzleSpace() override;
	virtual void RemovePuzzleObjectFromPuzzleSpace() override;

	UPROPERTY()
	UAudioComponent* PlaceJigsawPieceAudioComponent = nullptr;

	int static GetJigsawPieceRotationRoll(EJigsawPieceRotationRoll e);
	
		
};
