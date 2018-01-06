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
	
	return false;
}