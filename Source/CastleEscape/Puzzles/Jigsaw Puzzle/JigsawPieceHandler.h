// Copyright Henrique Rachti Assumpção 2020
#pragma once

#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include <CastleEscape\Puzzles\Jigsaw Puzzle\JigsawPiece.h>
#include <CastleEscape\PlayerController\GrabbedObjectHandler.h>
#include "JigsawPieceHandler.generated.h"

UCLASS()
class CASTLEESCAPE_API UJigsawPieceHandler : public UGrabbedObjectHandler
{	
	GENERATED_BODY()

	public:
		UJigsawPieceHandler();
		void MoveObject() override;
		void InitHandler(UPhysicsHandleComponent* PhysicsHandle, UGrabbedObject* GrabbedObject) override;
		void DestroyHandler() override;
		void SetupInputComponent();
		
		void SetInitialRotation();

		void UpdatePuzzleSpace();
		void SpinJigsawPiece();

	private:
	UInputComponent* InputComponent = nullptr;


};

