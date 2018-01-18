// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

// Forward declarations
class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	// Sets an intended movement magnitude between -1 (full reverse) and +1 (full forward)
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForwardReverse(float Throw);

	// Sets an intended turn magnitude which drives the left and right tracks opposite to one another. +1 turns full right, -1 full left
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurn(float Throw);
	
	// Request a move vector along pathfinding
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;


};
