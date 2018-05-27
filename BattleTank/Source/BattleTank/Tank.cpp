// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Projectile.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ATank::ATank() {
	PrimaryActorTick.bCanEverTick = true;
}

void ATank::Tick(float deltaT) {
	Super::Tick(deltaT);

	if (delayTimer > 0) {
		delayTimer -= GetWorld()->DeltaTimeSeconds;
	}

	updateReloadStatus();
}

void ATank::initialiseTankComponents(UTankAimingComponent* aimingComponent, UTankTurret* tankturret, UTankBarrel* tankBarrel) {
	TankAimingComponent = aimingComponent;
	TankAimingComponent->SetTurretReference(tankturret);
	TankAimingComponent->SetBarrelReference(tankBarrel);
	barrelForProjectileSpawn = tankBarrel;
}

void ATank::fireTurret() {
	if (delayTimer > 0 || ammoCount <= 0 || timeUntilReloaded > 0) { return; }
	if (!barrelForProjectileSpawn) { UE_LOG(LogTemp, Error, TEXT("No barrel registered on blueprint"));return; }
	if (!projectileBluePrint) { UE_LOG(LogTemp, Error, TEXT("No projectile registered on blueprint"));return; }

	FVector spawnLocation = barrelForProjectileSpawn->GetSocketLocation(FName("fireLocation"));
	FRotator spawnRotation = barrelForProjectileSpawn->GetSocketRotation(FName("fireLocation"));

	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileBluePrint, spawnLocation, spawnRotation);
	
	projectile->launchProjectile(firingVelocity);
	delayTimer += firingDelay;
	ammoCount--;
	if (ammoCount <= 0) { timeUntilReloaded += reloadTime; }
}

void ATank::BeginPlay() {
	Super::BeginPlay();
}

FVector ATank::getAimDirection() {
	if (!ensure(barrelForProjectileSpawn)) { return FVector().ZeroVector; }

	FVector forwardFacing = barrelForProjectileSpawn->GetForwardVector();
	forwardFacing.Normalize();

	return forwardFacing;
}

void ATank::updateReloadStatus() {
	if (timeUntilReloaded > 0) {
		timeUntilReloaded -= GetWorld()->DeltaTimeSeconds;
	} else if(timeUntilReloaded <= 0 && ammoCount <= 0) {
		ammoCount += maxAmmoCount;
	}
}

float ATank::getHealthPercentage() {
	return (float)hitPoints/100.f;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) {
	float damageToApply = FMath::Clamp<float>(DamageAmount, 0, hitPoints);

	if (DamageCauser && Cast<AProjectile>(DamageCauser)) {
		float seperationDistance = FMath::Abs(FVector::Dist(DamageCauser->GetActorLocation(), GetActorLocation()));
		float damageMultiplier = (1000 - FMath::Clamp<float>(seperationDistance, 0, 1000)) / 1000;

		if (seperationDistance > 300) {
			damageToApply *= damageMultiplier;
		}
	}

	hitPoints -= FMath::CeilToFloat(damageToApply);

	if (hitPoints <= 0) {
		OnDeath.Broadcast();
	}

	return damageToApply;
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::aimAt(FVector target) const {
	if (!TankAimingComponent) { UE_LOG(LogTemp, Warning, TEXT("Tank Aiming Component missing from Tank blueprint")); return; }
	TankAimingComponent->rotateTurret(target, firingVelocity);
}
