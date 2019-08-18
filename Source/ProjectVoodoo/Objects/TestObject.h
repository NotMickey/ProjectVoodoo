// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/ObjectBase.h"
#include "TestObject.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVOODOO_API ATestObject : public AObjectBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATestObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Code specific interaction logic
	virtual void OnInteract() override;

	UFUNCTION(BlueprintNativeEvent)
		void OnInteractBP();
};
