// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class AProjectile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEnvet, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;	

	FTankDelegate OnDeath;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsonly, Category = "Setup")
	int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

	virtual void BeginPlay() override;






};
