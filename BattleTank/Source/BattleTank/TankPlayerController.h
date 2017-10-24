// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float) override;

protected:
	UFUNCTION(BlueprintCallable, Category = Setup)
		ATank* GetControllerTank() const;

private:


	//Start the tank moving the barrel so that a shot would hit 
	// where the crosshay intersects the world
	void AimTowardCrosshair();

	//Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector&) const;

	bool GetLookVectorHitLocation(FVector, FVector&) const;

	UPROPERTY(EditAnyWhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnyWhere)
	float CrossHairYLocation = 0.33333;
	
	UPROPERTY(EditAnyWhere)
	float LineTraceRange = 1000000;
	
};
