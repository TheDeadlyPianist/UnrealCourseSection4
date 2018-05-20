// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::yawTurret(float relativeSpeed) {
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
	float deltaT = GetWorld()->DeltaTimeSeconds;
	float yawSpeed = relativeSpeed * maxYawSpeed * deltaT;
	float rawYawRotation = RelativeRotation.Yaw + yawSpeed;

	SetRelativeRotation(FRotator(0, rawYawRotation, 0));
}
