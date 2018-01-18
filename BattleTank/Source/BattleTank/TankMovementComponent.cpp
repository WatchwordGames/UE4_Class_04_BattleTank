// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


void UTankMovementComponent::IntendMoveForwardReverse(float Throw)
{
	if (!LeftTrack || !RightTrack) return;

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurn(float Throw)
{
	if (!LeftTrack || !RightTrack) return;

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// Not calling Super:: since we're totally hijacking the purpose of this method

	//UE_LOG(LogTemp, Warning, TEXT("Tank %s RequestDirectMove vector: %s"), *(GetOwner()->GetName()), *(MoveVelocity.GetSafeNormal().ToString()));

	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIIntendDirection = MoveVelocity.GetSafeNormal();

	IntendMoveForwardReverse(FVector::DotProduct(TankForward, AIIntendDirection));
}
