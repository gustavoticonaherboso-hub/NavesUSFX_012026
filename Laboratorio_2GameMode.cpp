// Copyright Epic Games, Inc. All Rights Reserved.

#include "Laboratorio_2GameMode.h"
#include "Laboratorio_2Pawn.h"

ALaboratorio_2GameMode::ALaboratorio_2GameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ALaboratorio_2Pawn::StaticClass();
}

