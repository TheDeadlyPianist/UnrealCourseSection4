// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBaseTracks.h"

void UTankBaseTracks::setThrottle(float relativeThrottle) {

	if (relativeThrottle > 1) {
		relativeThrottle = 1;
	} else if (relativeThrottle < -1) {
		relativeThrottle = -1;
	}
	FVector forceApplied = GetForwardVector() * relativeThrottle * maximumSpeedF;
	FVector forceLocation = GetComponentLocation();
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}
