// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Projectile.h"
#include "Components/AudioComponent.h"

// Sets default values
ATank::ATank() {
	PrimaryActorTick.bCanEverTick = true;
}

void ATank::Tick(float deltaT) {
	Super::Tick(deltaT);

	if (delayTimer > 0) {
		delayTimer -= GetWorld()->DeltaTimeSeconds;
	}
}

void ATank::initialiseTankComponents(UTankAimingComponent* aimingComponent, UTankTurret* tankturret, UTankBarrel* tankBarrel) {
	TankAimingComponent = aimingComponent;
	TankAimingComponent->SetTurretReference(tankturret);
	TankAimingComponent->SetBarrelReference(tankBarrel);
	barrelForProjectileSpawn = tankBarrel;
}

void ATank::fireTurret() {
	if (delayTimer > 0) { return; }
	if (!barrelForProjectileSpawn) { UE_LOG(LogTemp, Error, TEXT("No barrel registered on blueprint"));return; }
	if (!projectileBluePrint) { UE_LOG(LogTemp, Error, TEXT("No projectile registered on blueprint"));return; }

	FVector spawnLocation = barrelForProjectileSpawn->GetSocketLocation(FName("fireLocation"));
	FRotator spawnRotation = barrelForProjectileSpawn->GetSocketRotation(FName("fireLocation"));

	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileBluePrint, spawnLocation, spawnRotation);
	
	projectile->launchProjectile(firingVelocity);
	delayTimer += firingDelay;
}

void ATank::BeginPlay() {
	Super::BeginPlay();
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::aimAt(FVector target) const {
	if (!TankAimingComponent) { UE_LOG(LogTemp, Warning, TEXT("Tank Aiming Component missing from Tank blueprint")); return; }
	TankAimingComponent->rotateTurret(target, firingVelocity);
}
