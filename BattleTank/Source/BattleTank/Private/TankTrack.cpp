// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
  PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
  OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
  DriveTrack();
  ApplySidewaysForce();
  CurrentThrottle = 0.0f;
}

void UTankTrack::ApplySidewaysForce() {
  
  auto DeltaTime = GetWorld()->GetDeltaSeconds();

  // Calculate sideways slippage speed
  auto TrackVelocity = GetComponentVelocity();
  auto RightVelocity = GetRightVector();
  auto SlippageSpeed = FVector::DotProduct(TrackVelocity, RightVelocity);
  
  // Workout the required acceleration to counter it
  auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime) * RightVelocity;
  // Calculate and apply sideways force
  auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
  auto CorrectionForce = CorrectionAcceleration * TankRoot->GetMass() / 2; // two tracks
  
  TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
  CurrentThrottle = FMath::Clamp(CurrentThrottle + Throttle, -1.0f, 1.0f);
}

void UTankTrack::DriveTrack()
{
  auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
  auto ForceLocation = GetComponentLocation();
  auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
  
  TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
