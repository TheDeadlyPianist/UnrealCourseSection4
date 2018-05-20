// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBaseTracks.h"
#include "Engine/World.h"

UTankBaseTracks::UTankBaseTracks() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankBaseTracks::BeginPlay() {
	OnComponentHit.AddDynamic(this, &UTankBaseTracks::OnHit);
}

void UTankBaseTracks::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankBaseTracks::applySidewaysForce() {
	float DeltaTime = GetWorld()->DeltaTimeSeconds;

	FVector currentVector = GetComponentVelocity();
	FVector sidewaysVector = GetRightVector();
	float sidewaySlipRatio = FVector::DotProduct(currentVector, sidewaysVector);
	FVector correctionAcc = -(sidewaySlipRatio / DeltaTime * sidewaysVector);

	UStaticMeshComponent* tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector correctionForce = (tankRoot->GetMass() * correctionAcc) / 2;

	tankRoot->AddForce(correctionForce);
}

void UTankBaseTracks::setThrottle(float relativeThrottle) {
	currentThrottle = FMath::Clamp<float>(currentThrottle + relativeThrottle, -1, 1);
}

void UTankBaseTracks::driveTrack() {
	FVector forceApplied = GetForwardVector() * currentThrottle * maximumSpeedF;
	FVector forceLocation = GetComponentLocation();
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}

void UTankBaseTracks::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	driveTrack();
	applySidewaysForce();
	currentThrottle = 0; 
}
