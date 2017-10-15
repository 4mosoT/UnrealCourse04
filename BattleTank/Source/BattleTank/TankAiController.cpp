// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAiController.h"
#include "Engine/World.h"
#include "Tank.h"



void ATankAiController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank) {
		ControlledTank->AimtAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}
}


