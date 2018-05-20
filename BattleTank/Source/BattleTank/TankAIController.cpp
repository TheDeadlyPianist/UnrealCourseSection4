// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	goToPlayer();
	aimAtPlayer();
	getPossessedTank()->fireTurret();
}

void ATankAIController::aimAtPlayer() {
	if (getPlayerTank()) {
		FVector playerPosition = getPlayerTank()->GetActorLocation();
		getPossessedTank()->aimAt(playerPosition);
	}
}

ATank* ATankAIController::getPlayerTank() const {
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerPawn) { return nullptr; }
	return Cast<ATank>(playerPawn);
}

ATank* ATankAIController::getPossessedTank() {
	return Cast<ATank>(GetPawn());
}

void ATankAIController::goToPlayer() {
	if (!getPlayerTank()) { return; }
	MoveToActor(getPlayerTank(), acceptanceRadius);
}
