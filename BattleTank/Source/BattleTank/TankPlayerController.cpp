// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* abc = GetControlledTank();

	if (abc)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller is posessing: %s"), *(abc->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Did not get a tank"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	// Pointer protection
	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("AimTowardCrosshair HitLocation: %s"), *(HitLocation.ToString()));
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Get the crosshair position
	int32 ViewportSizeX;
	int32 ViewportSizeY;

	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = { ViewportSizeX * CrosshairXPosition, ViewportSizeY * CrosshairYPosition };

	// Deproject to world direction
	FVector ScreenWorldDirection;
	if (GetLookDirection(ScreenLocation, ScreenWorldDirection))
	{
		// Line trace along the look direction to see where we hit
		return GetLookVectorHitLocation(ScreenWorldDirection, HitLocation);
	}


	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& ScreenWorldDirection) const
{
	FVector ScreenWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, ScreenWorldLocation, ScreenWorldDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	float LineTraceRangeInCentimeters = 100000;
	FHitResult HitResult;
	
	FVector CameraViewPointLocation = PlayerCameraManager->GetCameraLocation();
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, CameraViewPointLocation, CameraViewPointLocation + (LookDirection * LineTraceRangeInCentimeters), ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		HitLocation = FVector(0);
		return false;
	}
}