// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

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

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
