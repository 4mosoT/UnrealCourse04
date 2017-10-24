// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{ 
	Aiming, 
	Reloading, 
	Locked
};

class UTankBarrel;
class UTankTurret;

//Holds barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void SetBarrelAndTurretReference(UTankBarrel*, UTankTurret*);


	//TODO add SetTurrentReference

	void AimAt(FVector, float);

protected:

	UPROPERTY(BlueprintReadOnly, Category = State)
		EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	void MoveTurrentAndBarrel(FVector);
	
};
