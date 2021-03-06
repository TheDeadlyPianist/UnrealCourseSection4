// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

private:
	void aimAtPlayer();
	
	ATank* getPlayerTank() const;

	ATank* getPossessedTank();

	void goToPlayer();

	UFUNCTION(BlueprintCallable)
		bool lookingAtPlayer();

	UPROPERTY(EditAnywhere)
		float acceptanceRadius = 8000;

	void SetPawn(APawn* InPawn) override;

	UFUNCTION()
		void OnTankDeath();
};
