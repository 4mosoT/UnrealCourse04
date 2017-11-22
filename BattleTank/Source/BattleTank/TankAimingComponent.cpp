// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankTurret.h"
#include "Engine/World.h"




// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	//So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void  UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) FiringStatus = EFiringStatus::Reloading; 
	else if (IsBarrelMoving())  FiringStatus = EFiringStatus::Aiming;
	else FiringStatus = EFiringStatus::Locked;

}

void UTankAimingComponent::SetBarrelAndTurretReference(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation) {

	if (!ensure(Barrel)) return;
	if (!ensure(Turret)) return;

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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveTurrentAndBarrel(AimDirection);
	}

}

void UTankAimingComponent::MoveTurrentAndBarrel(FVector AimDirection) {

	if (!ensure(Barrel && Turret)) { return;}
	// Difference between current barrel rotation and AimDirection
	FRotator BarrelRorator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRorator;
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);


}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) return false;
	return !Barrel->GetForwardVector().Equals(AimDirection, 0.05);
}


void UTankAimingComponent::Fire() {

	if (!ensure(Barrel && ProjectileBlueprint)) return;

	if (FiringStatus != EFiringStatus::Reloading) {
		//Spawn a projectile on the socket barrel location
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();

	}
}

