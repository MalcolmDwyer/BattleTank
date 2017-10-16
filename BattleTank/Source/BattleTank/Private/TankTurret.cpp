// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"




void UTankTurret::Rotate(float RelativeSpeed) {
  // Move the barrel the right amount this frame
  // Given max elevation speed, and the frame time
  
  RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
  auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
  auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
  
  auto NewRotation = FMath::Clamp<float>(RawNewRotation, -180, 180);
  SetRelativeRotation(FRotator(0, NewRotation, 0));
}
