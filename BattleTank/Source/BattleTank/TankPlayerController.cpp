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
  
  // Get world location through crosshair (linetrace)
  // If it hits landscape/enemy
    // tell controlled tank to aim at this point
}
