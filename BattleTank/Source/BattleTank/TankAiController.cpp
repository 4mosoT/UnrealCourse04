// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Engine/World.h"


void ATankAiController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) GetControllerTank()->AimtAt(GetPlayerTank()->GetActorLocation());
}

ATank*  ATankAiController::GetControllerTank() const {

	return Cast<ATank>(GetPawn());
}

ATank * ATankAiController::GetPlayerTank() const {
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void  ATankAiController::BeginPlay() {
	Super::BeginPlay();

	ATank* PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIPlayController not getting player tank"));
	}
	else UE_LOG(LogTemp, Warning, TEXT("AIPlayController getting player tank: %s"), *PlayerTank->GetName());


}

