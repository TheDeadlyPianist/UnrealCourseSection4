// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankMovementComponentNav.h"
#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "TankBarrel.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void Tick(float deltaT) override;

	UFUNCTION(BlueprintCallable, Category = Firing)
		void fireTurret();
	UFUNCTION(BlueprintCallable, Category = Setup)
		void initialiseTankComponents(UTankAimingComponent* aimingComponent, UTankTurret* tankturret, UTankBarrel* tankBarrel);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void aimAt(FVector target) const;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float firingDelay = 3;

	UPROPERTY(EditAnywhere, Category = Firing)
		float firingVelocity = 4000;

	UPROPERTY(BlueprintReadOnly, Category = Monitoring)
		float delayTimer = 0;

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> projectileBluePrint;

	UTankBarrel* barrelForProjectileSpawn;
};
