// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward declarations
class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	float CrosshairXPosition = 0.5;
	UPROPERTY(EditDefaultsOnly)
	float CrosshairYPosition = 0.333333;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

public:
	ATank* GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetLookDirection(FVector2D ScreenLocation, FVector& ScreenWorldDirection) const;
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
