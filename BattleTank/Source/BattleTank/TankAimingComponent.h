// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

UCLASS( ClassGroup=(TankComponents), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);

	void rotateTurret(FVector target, float firingVelocity);

	UPROPERTY(EditAnywhere)
		bool highArc = false;
	
private:
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	void MoveBarrel(FVector aimTowards);
};
