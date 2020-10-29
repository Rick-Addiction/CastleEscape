// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "CastleEscape.generated.h"

USTRUCT(BlueprintType)
struct FPuzzleSpace
{
    GENERATED_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ATriggerVolume* PuzzleSpace;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool bAvailable = true;
};