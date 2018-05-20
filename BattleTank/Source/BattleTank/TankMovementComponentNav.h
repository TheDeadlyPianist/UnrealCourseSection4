// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponentNav.generated.h"

class UTankBaseTracks;

/**
 * 
 */
UCLASS(ClassGroup = (TankComponents), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponentNav : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Movement)
		void intendMoveForward(float movement);
	UFUNCTION(BlueprintCallable, Category = Movement)
		void intendRotate(float rotation);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void initialiseTracks(UTankBaseTracks* leftTrackToSet, UTankBaseTracks* rightTrackToSet);

	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankBaseTracks* leftTracks = nullptr;
	UTankBaseTracks* rightTracks = nullptr;
};
