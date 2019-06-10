// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProjectVoodooGameMode.h"
#include "ProjectVoodooPlayerController.h"
#include "ProjectVoodooCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectVoodooGameMode::AProjectVoodooGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AProjectVoodooPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}