// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::RotateTurret(float RelativeSpeed)
{
	// Clamp the speed
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	float RotationChangeThisFrame = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	// Clamp to min/max elevation angles
	float NewRotation = RelativeRotation.Yaw + RotationChangeThisFrame;

	SetRelativeRotation(FRotator(0, NewRotation, 0));
}
