// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
  if (!LeftTrackToSet || !RightTrackToSet) { return; }
  
  LeftTrack = LeftTrackToSet;
  RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
  if (!LeftTrack || !RightTrack) { return; }
  
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(Throw);
  // TODO prevent double speed input from dual controls.
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
  if (!LeftTrack || !RightTrack) { return; }
  
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(-Throw);
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
  auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
  auto AIForwardIntention = MoveVelocity.GetSafeNormal();
  auto ForwardThrow = FVector::DotProduct(TankForwardDirection, AIForwardIntention);
  
  IntendMoveForward(ForwardThrow);
}
