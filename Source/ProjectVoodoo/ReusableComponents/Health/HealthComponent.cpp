// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

void UHealthComponent::OnComponentCreated()
{
	Owner = GetOwner();
}

void UHealthComponent::BeginPlay()
{
	Health = MaxHealth;
}

bool UHealthComponent::DoDamage(float damage, AActor* Instigator)
{
	if (bOverrideImmunity)
	{
		OnDamaged.Broadcast(Instigator, damage);
		return Damage(damage, Instigator);
	}

	if (!bDamagable || bImmune)
		return false;

	bImmune = true;
	GetWorld()->GetTimerManager().SetTimer(ImmunityTimerHandle, this, &UHealthComponent::EndImmunity, ImmunityTime);

	OnDamaged.Broadcast(Instigator, damage);

	return Damage(damage, Instigator);
}

bool UHealthComponent::DoHeal(float heal, AActor* Instigator)
{
	return Heal(heal, Instigator);
}

bool UHealthComponent::Damage(float damage, AActor* Instigator)
{
	Health -= damage;

	if (Health <= 0)
	{
		OnDeath.Broadcast(Instigator, damage);
		Health = 0;
	}

	return true;
}

bool UHealthComponent::Heal(float heal, AActor* Instigator)
{
	Health += heal;

	if (Health > MaxHealth)
	{
		OnHeal.Broadcast(Instigator, heal - (Health - MaxHealth));
		Health = MaxHealth;
	}
	else
		OnHeal.Broadcast(Instigator, heal);

	return true;
}

void UHealthComponent::EndImmunity()
{
	bImmune = false;
}
