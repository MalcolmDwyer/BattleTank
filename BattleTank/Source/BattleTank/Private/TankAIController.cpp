// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
  Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
  auto ControlledTank = Cast<ATank>(GetPawn());
  auto PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
  
  if (PlayerTank && ControlledTank) {
    ControlledTank->AimAt(PlayerTank->GetActorLocation());
    
    // TODO: Fire if ready
    ControlledTank->Fire();
  }

}
