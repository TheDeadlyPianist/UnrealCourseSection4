// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "TankBaseTracks.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (TankComponents), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBaseTracks : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void setThrottle(float relativeThrottle);

private:
	// Forward force in N
	UPROPERTY(EditAnywhere, Category = MovementSpeed)
		float maximumSpeedF = 40000000;
};
