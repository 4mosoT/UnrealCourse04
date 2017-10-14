// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::SetBarrelAndTurretReference(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {

	if (!Barrel) return;
	if (!Turret) return;

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel-> GetSocketLocation(FName("Projectile"));
	if (
		UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0.0,
			0.0,
			ESuggestProjVelocityTraceOption::DoNotTrace			
		)) {
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveTurrentAndBarrel(AimDirection);
	}

}

void UTankAimingComponent::MoveTurrentAndBarrel(FVector AimDirection) {


	// Difference between current barrel rotation and AimDirection
	FRotator BarrelRorator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRorator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);


}

