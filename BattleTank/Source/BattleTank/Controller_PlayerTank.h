// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Controller_PlayerTank.generated.h"

/**
 * 
 */

UCLASS()
class BATTLETANK_API AController_PlayerTank : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* getControlledTank() const;

	void BeginPlay() override;
	void SetTank(APawn * tankToUse);
	void Tick(float deltaTime) override;
	void aimTankTurret();
	bool getSightRayHitLocation(FHitResult &outHitLocation) const;

	UPROPERTY(EditAnywhere, Meta = (DisplayName = "Reticle X Position"))
		float reticleXPerc = 0.50f;
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "Reticle Y Position"))
		float reticleYPerc = 0.33f;

private:
	ATank* tankReference;
	bool getLookDirection(FVector2D reticleLocationOnScreen, FVector &lookDirection) const;
	bool getLookHitLocation(FHitResult &outHitLocation, FVector lookDirection) const;

	UFUNCTION()
		void playerKilled();
	
	UPROPERTY(EditAnywhere)
		float tankRange = 1000000;
};
