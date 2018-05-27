// Fill out your copyright notice in the Description page of Project Settings.

#include "Controller_PlayerTank.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"
#include "Runtime/Engine/Classes/Engine/World.h"

#define OUT

void AController_PlayerTank::BeginPlay() {
	Super::BeginPlay();
	SetTank(getControlledTank());
}

void AController_PlayerTank::SetTank(APawn* tankToUse) {
	if (!tankToUse) { return; }

	ATank* possessedTank = Cast<ATank>(tankToUse);
	possessedTank->OnDeath.AddUniqueDynamic(this, &AController_PlayerTank::playerKilled);
}

void AController_PlayerTank::Tick(float deltaTime) {
	Super::Tick(deltaTime);
	aimTankTurret();
}

ATank* AController_PlayerTank::getControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void AController_PlayerTank::aimTankTurret() {
	if (!getControlledTank()) { return; }

	FHitResult hitLocation;

	if (getSightRayHitLocation(hitLocation)) {
		FVector hitPoint = hitLocation.ImpactPoint;
		getControlledTank()->aimAt(hitPoint);
	}
}

bool AController_PlayerTank::getSightRayHitLocation(FHitResult &outHitLocation) const {

	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	FVector2D reticlePositionOnScreen = FVector2D(
		viewportSizeX*reticleXPerc,
		viewportSizeY*reticleYPerc
	);

	FVector lookDirection;

	if (getLookDirection(reticlePositionOnScreen, lookDirection)) {
		return getLookHitLocation(outHitLocation, lookDirection);;
	} else {
		return false;
	}
}

bool AController_PlayerTank::getLookDirection(FVector2D reticleLocationOnScreen, FVector &lookDirection) const {

	FVector worldPosition;

	return DeprojectScreenPositionToWorld(
		reticleLocationOnScreen.X,
		reticleLocationOnScreen.Y,
		worldPosition,
		lookDirection
	);
}

bool AController_PlayerTank::getLookHitLocation(FHitResult &outHitLocation, FVector lookDirection) const {
	FVector curPos = PlayerCameraManager->GetCameraLocation();

	return GetWorld()->LineTraceSingleByChannel(
		outHitLocation,
		curPos,
		curPos + (lookDirection * tankRange),
		ECC_Camera
	);
}

void AController_PlayerTank::playerKilled() {
	UE_LOG(LogTemp, Warning, TEXT("asdgasgasdg"));
	StartSpectatingOnly();
}
