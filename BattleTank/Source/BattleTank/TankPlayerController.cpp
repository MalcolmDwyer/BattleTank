// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
  Super::BeginPlay();
    
  ControlledTank = GetControlledTank();
  
  if (ControlledTank) {
    UE_LOG(LogTemp, Warning, TEXT(" Got Tank -> %s"), *(ControlledTank->GetName()))
  }
  else {
    UE_LOG(LogTemp, Error, TEXT("No tank in player controller"))
  }
}

void ATankPlayerController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  AimTowardsCrossHair();
}



ATank* ATankPlayerController::GetControlledTank() const
{
  return Cast<ATank>(GetPawn());
}



void ATankPlayerController::AimTowardsCrossHair()
{
  if (!GetControlledTank()) {
    return;
  }
  
  FVector HitLocation; // Out parameter
  
  if(GetSightRayHitLocation(HitLocation)) {
//    UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString())
    
    
  }
  
  // Get world location through crosshair (linetrace)
  // If it hits landscape/enemy
    // tell controlled tank to aim at this point
}


bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
  OutHitLocation.Set(1.0f, 2.0f, 3.0f);
  
  // Find the crosshair position
  int32 ViewportSizeX, ViewportSizeY;
  GetViewportSize(ViewportSizeX, ViewportSizeY);
  FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
  //UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString())
  
  
  // Deproject the screen position of the cross to a world direction
  // Line trace to see what we hit (up to max range)
  
  return true;
}

