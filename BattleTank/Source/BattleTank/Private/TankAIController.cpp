// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
  Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
  auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
  if (!ensure(AimingComponent)) { return; }
  
  auto PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
  
  if (PlayerTank) {
    MoveToActor(PlayerTank, AcceptanceRadius);
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    AimingComponent->Fire();
  }
}
