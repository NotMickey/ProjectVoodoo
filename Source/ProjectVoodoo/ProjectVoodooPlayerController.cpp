// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProjectVoodooPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Runtime/Core/Public/Math/Rotator.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectVoodooCharacter.h"
#include "Engine/World.h"

#include "Objects/ObjectBase.h"

AProjectVoodooPlayerController::AProjectVoodooPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AProjectVoodooPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

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

	InputComponent->BindAxis("MoveForward", this, &AProjectVoodooPlayerController::OnUpKeyPressed);
	InputComponent->BindAxis("MoveRight", this, &AProjectVoodooPlayerController::OnRightKeyPressed);

	InputComponent->BindAction("Interact", IE_Released, this, &AProjectVoodooPlayerController::OnInteractKeyPressed);
}

void AProjectVoodooPlayerController::OnUpKeyPressed(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * speed;
}

void AProjectVoodooPlayerController::OnRightKeyPressed(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * speed;
}

void AProjectVoodooPlayerController::OnInteractKeyPressed()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Camera, false, Hit);

	AActor* hitActor = Hit.GetActor();

	if (hitActor->IsA(AObjectBase::StaticClass()))
	{
		AObjectBase* object = Cast<AObjectBase>(hitActor);

		if (GetPawn()->GetDistanceTo(object) <= object->interactionDistance)
			object->OnInteract();
	}
}
