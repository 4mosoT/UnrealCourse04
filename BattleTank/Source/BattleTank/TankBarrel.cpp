// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	// Move the barrel the right ammount this frame
	// Given a max elevation speed, and the frame size 
	float RawNewElevation = RelativeRotation.Pitch + (FMath::Clamp(RelativeSpeed,-1.0f,1.0f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds);
	SetRelativeRotation(FRotator(
		FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees),
		0, 0));

}