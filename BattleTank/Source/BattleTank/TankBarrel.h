// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (TankComponents), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = TankAiming)
		float maxBarrelAngle = 40;
	UPROPERTY(EditAnywhere, Category = TankAiming)
		float minBarrelAngle = 0;
	UPROPERTY(EditAnywhere, Category = TankAiming)
		float maxBarrelSpeed = 5;

public:
	// -1 is max down movement, 1 is max up movement
	void ElevateBarrel(float relativeSpeed);
};
