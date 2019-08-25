// Fill out your copyright notice in the Description page of Project Settings.


#include "TestObject.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"

ATestObject::ATestObject()
{
	// Don't need Actor tick just yet...
	PrimaryActorTick.SetTickFunctionEnable(false);
}

void ATestObject::BeginPlay()
{
	Super::BeginPlay();

	//OnInteract();
}

void ATestObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestObject::OnInteract()
{
	// Any logic that does not need to be set up in Blueprints should go here.

	// Called to run Blueprint implemented logic
	OnInteractBP();
}

void ATestObject::OnInteractBP_Implementation()
{
	// Any default implementation goes here
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "Calling the default because no BP implementation found!!");
}
