// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEnvet, AController * EventInstigator, AActor * DamageCauser)
{
//	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEnvet, EventInstigator, DamageCauser);
//	float DamageToApply = FMath::Clamp(ActualDamage, 0.f, Health);
//	if (ActualDamage > 0) {
		
//		Health -= DamageToApply;
//	}
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	return DamageToApply;
}
