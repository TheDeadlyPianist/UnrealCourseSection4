// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponentNav.h"
#include "TankBaseTracks.h"

void UTankMovementComponentNav::intendRotate(float rotation) {
	if (!leftTracks || !rightTracks) { return; }
	leftTracks->setThrottle(rotation * 0.8);
	rightTracks->setThrottle(-rotation * 0.8);
}

void UTankMovementComponentNav::initialiseTracks(UTankBaseTracks* leftTrackToSet, UTankBaseTracks* rightTrackToSet) {
	if ( !leftTrackToSet || !rightTrackToSet ) { return; }
	leftTracks = leftTrackToSet;
	rightTracks = rightTrackToSet;
}

void UTankMovementComponentNav::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) {
	FVector aiForwardIntention = MoveVelocity.GetSafeNormal();
	FVector forwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();

	float ratioOfCloseness = FVector::DotProduct(aiForwardIntention, forwardDirection);
	float ratioOfFace = FVector::CrossProduct(aiForwardIntention, forwardDirection).Z;

	intendMoveForward(ratioOfCloseness);
	intendRotate(-ratioOfFace);
}

void UTankMovementComponentNav::intendMoveForward(float movement) {
	if ( !leftTracks || !rightTracks ) { return; }
	leftTracks->setThrottle(movement);
	rightTracks->setThrottle(movement);
}
