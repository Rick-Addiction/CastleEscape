// Copyright Henrique Rachti Assumpção 2020

#include "ObjectHandler.h"

#include "Puzzles/Gems Puzzle/Gem.h"
#include "Puzzles/Jigsaw Puzzle/JigsawPiece.h"

EObjectType UObjectHandler::GetObjectType(AActor* ObjectSought){

    if (ObjectSought->FindComponentByClass<UJigsawPiece>())
        return EObjectType::Jigsaw_Piece;
    else if (ObjectSought->FindComponentByClass<UGem>())
        return EObjectType::Gem;
    else
        return EObjectType::Undefined;
}






