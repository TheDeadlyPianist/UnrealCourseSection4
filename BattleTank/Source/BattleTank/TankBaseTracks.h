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
	UTankBaseTracks();
	void BeginPlay() override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void setThrottle(float relativeThrottle);

	void driveTrack(float currentThrottle);

private:
	// Forward force in N
	UPROPERTY(EditAnywhere, Category = MovementSpeed)
		float maximumSpeedF = 40000000;

	TArray<class ASprungWheel*> GetWheels() const;
};
