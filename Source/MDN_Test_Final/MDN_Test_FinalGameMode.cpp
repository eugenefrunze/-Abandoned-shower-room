// Copyright Epic Games, Inc. All Rights Reserved.

#include "MDN_Test_FinalGameMode.h"
#include "MDN_Test_FinalCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMDN_Test_FinalGameMode::AMDN_Test_FinalGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
