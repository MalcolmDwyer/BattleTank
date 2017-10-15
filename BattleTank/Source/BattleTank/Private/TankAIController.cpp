// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
  Super::BeginPlay();
  
  auto ControlledTank = GetControlledTank();
  auto PlayerTank = GetPlayerTank();
  
  if (PlayerTank) {
    UE_LOG(LogTemp, Warning, TEXT("AI Tank found player Tank -> %s"), *(PlayerTank->GetName()))
  }
  else {
    UE_LOG(LogTemp, Error, TEXT("No player tank in AI"))
  }
}

void ATankAIController::Tick(float DeltaTime)
{
  AimTowardsPlayer();
}

void ATankAIController::AimTowardsPlayer() const
{
  auto PlayerTank = GetPlayerTank();
  auto ControlledTank = GetControlledTank();
  
  if (PlayerTank && ControlledTank) {
    ControlledTank->AimAt(PlayerTank->GetActorLocation());
  }
}

ATank* ATankAIController::GetControlledTank() const
{
  return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
  auto PlayerPawn = (GetWorld()->GetFirstPlayerController()->GetPawn());
  
  if (!PlayerPawn) {
    return nullptr;
  }
  
  return Cast<ATank>(PlayerPawn);
}

