// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBaseTracks.h"
#include "Engine/World.h"
#include "SprungWheel.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.h"

UTankBaseTracks::UTankBaseTracks() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankBaseTracks::BeginPlay() {
}

void UTankBaseTracks::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankBaseTracks::setThrottle(float relativeThrottle) {
	float currentThrottle = FMath::Clamp<float>(relativeThrottle, -1, 1);
	driveTrack(currentThrottle);
}

void UTankBaseTracks::driveTrack(float currentThrottle) {
	float forceApplied = currentThrottle * maximumSpeedF;
	auto allWheels = GetWheels();
	float forcePerWheel = forceApplied / allWheels.Num();

	for (ASprungWheel* wheel : allWheels) {
		wheel->addDrivingForce(forcePerWheel);
	}
}

TArray<ASprungWheel*> UTankBaseTracks::GetWheels() const {
	TArray<ASprungWheel*> resultArray;
	TArray<USceneComponent*> children;
	GetChildrenComponents(true, children);
	for (USceneComponent* child : children) {
		USpawnPoint* spawnPoint = Cast<USpawnPoint>(child);
		if (!spawnPoint) continue;

		AActor* spawnedActor = spawnPoint->getSpawnedActor();
		ASprungWheel* sprungWheel = Cast<ASprungWheel>(spawnedActor);
		if (!sprungWheel) continue;

		resultArray.Add(sprungWheel);
	}
	return resultArray;
}
