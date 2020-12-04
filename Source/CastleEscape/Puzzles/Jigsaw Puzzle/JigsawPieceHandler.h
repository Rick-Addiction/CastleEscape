// Copyright Henrique Rachti Assump��o 2020
#pragma once

#include "CoreMinimal.h"
#include "PlayerController/ObjectHandler/GrabbableObjectHandler.h"

#include "JigsawPieceHandler.generated.h"

UCLASS()
class CASTLEESCAPE_API UJigsawPieceHandler : public UGrabbableObjectHandler
{	
	GENERATED_BODY()

	public:
		UJigsawPieceHandler();
		virtual void Handle() override;
		virtual void MoveObject() override;
		virtual void InitHandler(AActor* GrabbedObject) override;
		virtual void DestroyHandler() override;
		virtual void UpdatePuzzleSpace() override;

		void SetupInputComponent();		
		void SetInitialRotation() const;		
		void SpinJigsawPiece();

};

