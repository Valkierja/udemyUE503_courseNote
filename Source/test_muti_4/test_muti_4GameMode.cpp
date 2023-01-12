// Copyright Epic Games, Inc. All Rights Reserved.

#include "test_muti_4GameMode.h"
#include "test_muti_4Character.h"
#include "UObject/ConstructorHelpers.h"

Atest_muti_4GameMode::Atest_muti_4GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
