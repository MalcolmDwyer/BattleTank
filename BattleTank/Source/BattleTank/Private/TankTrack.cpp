// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"




void UTankTrack::SetThrottle(float Throttle)
{

  auto Name = GetName();
  auto Time = GetWorld()->GetTimeSeconds();
  UE_LOG(LogTemp, Warning, TEXT("%f %s Throttle %f"), Time, *Name, Throttle)
  
}
