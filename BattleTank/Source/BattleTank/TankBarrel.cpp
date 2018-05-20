// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::ElevateBarrel(float relativeSpeed) {
	float deltaT = GetWorld()->DeltaTimeSeconds;
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
	float elevationSpeed = relativeSpeed * maxBarrelSpeed * deltaT;
	float rawNewElevation = RelativeRotation.Pitch + elevationSpeed;
	float clampedElevation = FMath::Clamp<float>(rawNewElevation, minBarrelAngle, maxBarrelAngle);

	SetRelativeRotation(FRotator(clampedElevation, 0, 0));
}
