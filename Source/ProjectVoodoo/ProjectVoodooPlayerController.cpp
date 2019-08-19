// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProjectVoodooPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Runtime/Core/Public/Math/Rotator.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectVoodooCharacter.h"
#include "Engine/World.h"

AProjectVoodooPlayerController::AProjectVoodooPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AProjectVoodooPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	/*if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}*/

	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Camera, false, Hit);

	FRotator PawnRotation = GetPawn()->GetActorRotation();

	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetPawn()->GetActorLocation(), Hit.ImpactPoint);
	FRotator TargetRotation = FRotator(0.0f, Rotation.Yaw, 0.0f);

	GetPawn()->SetActorRotation(UKismetMathLibrary::RInterpTo(PawnRotation, TargetRotation, 0.5f, 0.5f));

	if (!CurrentVelocity.IsNearlyZero())
	{
		Up = FRotator(0.0f, 0.0f, GetPawn()->GetControlRotation().Yaw);
		GetPawn()->AddMovementInput(UKismetMathLibrary::GetForwardVector(Up), CurrentVelocity.X);

		Right = FRotator(0.0f, 0.0f, GetPawn()->GetControlRotation().Yaw);
		GetPawn()->AddMovementInput(UKismetMathLibrary::GetRightVector(Right), CurrentVelocity.Y);
	}
}

void AProjectVoodooPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AProjectVoodooPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AProjectVoodooPlayerController::OnSetDestinationReleased);

	InputComponent->BindAxis("MoveForward", this, &AProjectVoodooPlayerController::OnUpKeyPressed);
	InputComponent->BindAxis("MoveRight", this, &AProjectVoodooPlayerController::OnRightKeyPressed);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AProjectVoodooPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AProjectVoodooPlayerController::MoveToTouchLocation);
}

void AProjectVoodooPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AProjectVoodooPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AProjectVoodooPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AProjectVoodooPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AProjectVoodooPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AProjectVoodooPlayerController::OnUpKeyPressed(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * speed;
}

void AProjectVoodooPlayerController::OnRightKeyPressed(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * speed;
}
