// Copyright Henrique Rachti Assumpção 2020

#include "ObjectHandler.h"


#include "Puzzles/Bells Puzzle/Bell/Bell.h"
#include "Puzzles/Bells Puzzle/MelodySphere/MelodySphere.h"
#include "Puzzles/Gems Puzzle/Gem.h"
#include "Puzzles/Jigsaw Puzzle/JigsawPiece.h"
#include "Puzzles/Pipes Puzzle/PipeValve.h"

EObjectType UObjectHandler::GetObjectType(AActor* ObjectSought){

    if (ObjectSought->FindComponentByClass<UJigsawPiece>())
        return EObjectType::Jigsaw_Piece;
    else if (ObjectSought->FindComponentByClass<UGem>())
        return EObjectType::Gem;
    else if (ObjectSought->FindComponentByClass<UBell>())
        return EObjectType::Bell;
    else if (ObjectSought->FindComponentByClass<UMelodySphere>())
        return EObjectType::MelodySphere;
    else if (ObjectSought->FindComponentByClass<UPipeValve>())
        return EObjectType::PipeValve;
    else
        return EObjectType::Undefined;
}






