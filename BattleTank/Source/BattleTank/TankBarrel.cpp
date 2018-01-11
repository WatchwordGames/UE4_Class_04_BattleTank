// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	// Clamp the speed
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	float ElevationChangeThisFrame = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	// Clamp to min/max elevation angles
	float NewElevation = FMath::Clamp(RelativeRotation.Pitch + ElevationChangeThisFrame, MinElevationDegrees, MaxElevationDegrees);
	
	SetRelativeRotation(FRotator(NewElevation, 0, 0));
}
