// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProjectVoodooPlayerController.generated.h"

UCLASS()
class AProjectVoodooPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AProjectVoodooPlayerController();

	UPROPERTY(BlueprintReadWrite)
		float speed = 200.0f;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Input handlers for WSAD controls*/
	void OnUpKeyPressed(float AxisValue);
	void OnRightKeyPressed(float AxisValue);

	/** Input handlers for mouse controls*/
	void OnInteractKeyPressed();
	void OnActionKeyPressed();
	void OnActionKeyReleased();

private:
	FVector CurrentVelocity = FVector::ZeroVector;
	FRotator Up = FRotator::ZeroRotator;
	FRotator Right = FRotator::ZeroRotator;
};


