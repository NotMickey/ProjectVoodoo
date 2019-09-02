// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponRanged.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Engine/World.h"

UWeaponRanged::UWeaponRanged()
{
	// Bind the timer functions
	beginReloadTimerDel.BindUFunction(this, FName("OnReload"));
	reloadTimerDel.BindUFunction(this, FName("OnEndReload"));
}

void UWeaponRanged::FireWeapon()
{
	// Any logic that does not need to be set up in Blueprints should go here.
	if (isReloading)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Can't Fire! - Weapon Reloading!");
		return;
	}

	GetWorld()->GetTimerManager().ClearTimer(timerHandle);

	// Called to run Blueprint component implemented logic
	OnFireWeaponBP();
}

void UWeaponRanged::OnFireWeaponBP_Implementation()
{
	// Any default implementation goes here
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "Fire Weapon - Default!");
}

void UWeaponRanged::OnBeginReload()
{
	if (isReloading || !canReload)
		return;

	GetWorld()->GetTimerManager().SetTimer(timerHandle, beginReloadTimerDel, 1.0f, false);
}

void UWeaponRanged::OnReload()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Reload started!");

	// Any logic that does not need to be set up in Blueprints should go here.
	isReloading = true;

	GetWorld()->GetTimerManager().ClearTimer(timerHandle);
	GetWorld()->GetTimerManager().SetTimer(timerHandle, reloadTimerDel, 2.5f, false);

	// Called to run Blueprint component implemented logic
	OnReloadWeaponBP();
}

void UWeaponRanged::OnEndReload()
{
	isReloading = false;
	GetWorld()->GetTimerManager().ClearTimer(timerHandle);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Reload complete!");
}

void UWeaponRanged::OnReloadWeaponBP_Implementation()
{
	// Any default implementation goes here
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Reload Weapon - Default!");
}
