// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet) {
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet) {
	Turret = TurretToSet;
}

void UTankAimingComponent::rotateTurret(FVector target, float firingVelocity) {
	if ( !Barrel ) { return; }
	
	FVector fireLocation = Barrel->GetSocketLocation(FName("fireLocation"));
	FVector finalAimVector;

	bool canMakeShot = UGameplayStatics::SuggestProjectileVelocity(
		this,
		finalAimVector,
		fireLocation,
		target,
		firingVelocity,
		false,
		0.f, 0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (canMakeShot) {
		FVector aimDirection = finalAimVector.GetSafeNormal();
		MoveBarrel(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector aimTowards) {

	FString name = GetOwner()->GetName();

	FRotator barrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator aimRotator = aimTowards.Rotation();
	FRotator rotationDelta = aimRotator - barrelRotator;

	Barrel->ElevateBarrel(rotationDelta.Pitch);
	Turret->yawTurret(rotationDelta.Yaw);

}
