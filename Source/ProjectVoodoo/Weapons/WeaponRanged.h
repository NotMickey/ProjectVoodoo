// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponBase.h"
#include <Runtime/Engine/Public/TimerManager.h>
#include "WeaponRanged.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVOODOO_API UWeaponRanged : public UWeaponBase
{
	GENERATED_BODY()

public:
	UWeaponRanged();

	virtual void FireWeapon() override;

	UFUNCTION(BlueprintNativeEvent)
	void OnFireWeaponBP();

	/** Logic for reloading the current primary weapon */
	virtual void OnBeginReload() override;

	UFUNCTION()
	void OnReload();

	UFUNCTION()
	void OnEndReload();

	UFUNCTION(BlueprintNativeEvent)
	void OnReloadWeaponBP();

	UPROPERTY(BlueprintReadWrite, Category = "Weapon Properties")
	bool canReload = false;

	UPROPERTY(BlueprintReadOnly)
	bool isReloading = false;

private:
	FTimerDelegate beginReloadTimerDel;
	FTimerDelegate reloadTimerDel;
	FTimerHandle timerHandle;
};
