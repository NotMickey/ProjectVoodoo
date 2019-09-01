// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDamaged, AActor*, Instigator, float, Amount);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTVOODOO_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void OnComponentCreated() override;

	UFUNCTION(BlueprintCallable)
	bool DoDamage(float damage, AActor* Instigator);

	UFUNCTION(BlueprintCallable)
	bool DoHeal(float heal, AActor* Instigator);

	UPROPERTY(BlueprintAssignable)
	FDamaged OnDamaged;

	UPROPERTY(BlueprintAssignable)
	FDamaged OnDeath;

	UPROPERTY(BlueprintAssignable)
	FDamaged OnHeal;

protected:
	UPROPERTY(BlueprintReadOnly)
	AActor* Owner = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth = 100;

	UPROPERTY(BlueprintReadOnly, meta = (ClampMin = 0))
	float Health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinDamage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDamagable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bOverrideImmunity = false;

	UPROPERTY(BlueprintReadOnly)
	bool bImmune = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ImmunityTime = 0.5f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	bool Damage(float damage, AActor* Instigator);

	UFUNCTION()
	bool Heal(float heal, AActor* Instigator);

	UFUNCTION()
	void EndImmunity();

	FTimerHandle ImmunityTimerHandle;
};
