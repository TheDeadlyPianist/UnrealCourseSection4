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
	if (lookingAtPlayer()) {
		getPossessedTank()->fireTurret();
	}
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

bool ATankAIController::lookingAtPlayer() {
	if (!getPlayerTank()) { return false; }
	if (!getPossessedTank()) { return false; }

	FVector playerDirection = getPlayerTank()->GetActorLocation() - getPossessedTank()->GetActorLocation();
	FVector barrelFacingDirection = getPossessedTank()->getAimDirection();

	float differenceRatio = FVector::DotProduct(playerDirection.GetSafeNormal2D(), barrelFacingDirection.GetSafeNormal2D());

	if (differenceRatio > 0.98) { return true; } else { return false; }
}

void ATankAIController::SetPawn(APawn * InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath() {
	if (!getPossessedTank()) { return; }
	getPossessedTank()->DetachFromControllerPendingDestroy();
}

void ATankAIController::goToPlayer() {
	if (!getPlayerTank()) { return; }
	MoveToActor(getPlayerTank(), acceptanceRadius);
}
