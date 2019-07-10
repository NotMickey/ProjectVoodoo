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

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	/** Input handlers for WSAD controls*/
	void OnUpKeyPressed(float AxisValue);
	void OnRightKeyPressed(float AxisValue);

private:
	FVector currentVelocity = FVector::ZeroVector;
};


