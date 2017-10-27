// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h" // so we can implement OnDeath

void ATankAIController::BeginPlay()
{
  Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
  Super::SetPawn(InPawn);
  if (InPawn) {
    auto PossessedTank = Cast<ATank>(InPawn);
    
    if (!ensure(PossessedTank)) { return; }
    
    // TODO: subscribe our local method to tank's death event
    PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
  }
}

void ATankAIController::Tick(float DeltaTime)
{
  auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
  if (!ensure(AimingComponent)) { return; }
  
  auto PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
  
  if (PlayerTank) {
    MoveToActor(PlayerTank, AcceptanceRadius);
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    
    if (AimingComponent->GetFiringState() == EFiringState::Locked) {
      AimingComponent->Fire();
    }
  }
}

void ATankAIController::OnPossessedTankDeath()
{
  UE_LOG(LogTemp, Warning, TEXT("AI Controller OnTankDeath"))
}
