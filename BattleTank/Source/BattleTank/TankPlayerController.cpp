// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
  Super::BeginPlay();
  
  UE_LOG(LogTemp, Warning, TEXT("Player Controller begin play"));
  
  auto ControlledTank = GetControlledTank();
  if (ControlledTank) {
    UE_LOG(LogTemp, Warning, TEXT(" Got Tank -> %s"), *(ControlledTank->GetName()))
  }
  else {
    UE_LOG(LogTemp, Error, TEXT("No tank in player controller"))
  }
}



ATank* ATankPlayerController::GetControlledTank() const
{
  return Cast<ATank>(GetPawn());
}



