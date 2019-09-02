// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponBase.generated.h"


UENUM(BlueprintType)
enum WeaponType
{
	Enum_Item1 UMETA(DisplayName = "Melee"),
	Enum_Item2 UMETA(DisplayName = "Ranged"),
	Enum_Item3 UMETA(DisplayName = "Unarmed"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTVOODOO_API UWeaponBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnBeginReload() {}

	virtual void FireWeapon() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		TEnumAsByte<WeaponType> weaponType;
};
