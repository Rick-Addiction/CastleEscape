// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "CastleEscape.generated.h"

UENUM(BlueprintType)
enum class EPuzzleRotation : uint8 {

    UP UMETA(DisplayName = "UP"),
    LEFT UMETA(DisplayName = "LEFT"),
    DOWN UMETA(DisplayName = "DOWN"),    
    RIGHT UMETA(DisplayName = "RIGHT")
    
};

USTRUCT(BlueprintType)
struct FPuzzleSpace
{
    GENERATED_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ATriggerVolume* PuzzleSpace;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        AActor* PuzzlePieceExpected;

    AActor* CurrentPuzzlePiecePlaced;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        EPuzzleRotation PuzzlePieceRotationExpected;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EPuzzleRotation CurrentPuzzlePieceRotation;

    bool bAvailable = true;
};