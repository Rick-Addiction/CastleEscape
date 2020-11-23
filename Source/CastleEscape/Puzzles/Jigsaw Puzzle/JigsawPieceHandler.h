// Copyright Henrique Rachti Assump��o 2020
#pragma once

#include "CoreMinimal.h"
#include "CastleEscape/PlayerController/GrabbedObjectHandler.h"
#include "JigsawPieceHandler.generated.h"

UCLASS()
class CASTLEESCAPE_API UJigsawPieceHandler : public UGrabbedObjectHandler
{	
	GENERATED_BODY()

	public:
		UJigsawPieceHandler();
		virtual void MoveObject() override;
		virtual void InitHandler(UPhysicsHandleComponent* PhysicsHandle, UGrabbedObject* GrabbedObject) override;
		virtual void DestroyHandler() override;
		virtual void UpdatePuzzleSpace() override;

		void SetupInputComponent();		
		void SetInitialRotation() const;		
		void SpinJigsawPiece();

	private:
	
	UPROPERTY()
	UInputComponent* InputComponent = nullptr;


};

