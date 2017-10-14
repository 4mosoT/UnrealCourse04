// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Rotate(float RelativeSpeed) {
	float RawRotation = RelativeRotation.Yaw +  MaxDegreesPerSecond * FMath::Clamp(RelativeSpeed, -1.0f, 1.0f) * GetWorld()->DeltaTimeSeconds;
	SetRelativeRotation(FRotator(0.0, RawRotation, 0.0));
}


