// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) return;

	// Fires event to blueprint to build UI
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) return;

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	// Pointer protection
	if (!ensure(AimingComponent)) return;

	FVector HitLocation;
	
	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
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

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe local method to tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
	//UE_LOG(LogTemp, Error, TEXT("THE PLAYER TANK IS DEAD!"));
}