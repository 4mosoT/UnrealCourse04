// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAiController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Engine/World.h"



void ATankAiController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(PlayerTank && ControlledTank)) return;
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	MoveToActor(PlayerTank, AcceptanceRadius);
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked) AimingComponent->Fire();
	
}

void ATankAiController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		ATank* PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank)) return;
		PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAiController::OnTankDeath);
	}
}

void ATankAiController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("AITank Destroyed"))
}
