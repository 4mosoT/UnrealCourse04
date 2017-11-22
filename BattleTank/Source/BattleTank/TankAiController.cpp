// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAiController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"



void ATankAiController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(PlayerTank && ControlledTank)) return;
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	MoveToActor(PlayerTank, AcceptanceRadius);
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	AimingComponent->Fire();
	
}


