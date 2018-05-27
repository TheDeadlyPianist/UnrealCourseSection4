// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetConstraints();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Suspension)
		USphereComponent* wheel = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Suspension)
		USphereComponent* axle = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Suspension)
		UPhysicsConstraintComponent* massToAxleConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Suspension)
		UPhysicsConstraintComponent* axleToWheelConstraint = nullptr;
	
	UFUNCTION()
		void addDrivingForce(float forceMagnitude);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void applyForce();
	float totalForceThisFrame = 0;
};
