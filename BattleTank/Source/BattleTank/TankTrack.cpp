// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Speed along right vector of tank
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	
	// Corrective acceleration for slippage
	FVector CorrectionAcceleration = -(SlippageSpeed / DeltaTime) * GetRightVector();

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	FVector CorrectionForcePerTrack = ((TankRoot->GetMass()) * CorrectionAcceleration) / 2.0f;

	TankRoot->AddForce(CorrectionForcePerTrack);
}

void UTankTrack::SetThrottle(float Throttle)
{
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
