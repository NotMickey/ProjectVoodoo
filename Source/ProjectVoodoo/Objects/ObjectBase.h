// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectBase.generated.h"

UENUM(BlueprintType)
enum ObjectName
{
	Enum_Item1 UMETA(DisplayName = "Item1"),
	Enum_Item2 UMETA(DisplayName = "Item2"),
};

UCLASS(Abstract)
class PROJECTVOODOO_API AObjectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Handle any code specific logic/calculations here
	virtual void OnInteract() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object")
		TEnumAsByte<ObjectName> objectName;
};
