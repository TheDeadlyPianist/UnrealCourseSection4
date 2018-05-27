// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankMovementComponentNav.h"
#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "TankBarrel.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class AProjectile;
class UParticleSystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

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
		float firingVelocity = 10000;

	UPROPERTY(BlueprintReadOnly, Category = Monitoring)
		float delayTimer = 0;

	UFUNCTION(BlueprintCallable)
		float getTimerDelay() { return delayTimer; }

	UFUNCTION(BlueprintCallable)
		FVector getAimDirection();

	UPROPERTY(EditAnywhere, Category = Firing)
		int32 ammoCount = 3;

	UPROPERTY(EditAnywhere, Category = Firing)
		int32 maxAmmoCount = 3;

	UFUNCTION(BlueprintCallable, Category = Firing)
		int32 getAmmoCount() { return ammoCount; };

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float reloadTime = 5;

	void updateReloadStatus();

	float timeUntilReloaded = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		float hitPoints = 100.f;

	UFUNCTION(BlueprintCallable)
		float getHitPoints() { return hitPoints; }

	UFUNCTION(BlueprintPure, Category = Health)
		float getHealthPercentage();

	UPROPERTY(BlueprintAssignable, Category = DeathCallable)
		FOnDeath OnDeath;

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> projectileBluePrint;

	UTankBarrel* barrelForProjectileSpawn;

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;
};
