// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Misc/AssertionMacros.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
  Super::BeginPlay();
  auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
  if (!ensure(AimingComponent)) { return; }
  FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
  Super::SetPawn(InPawn);
  if (InPawn) {
    auto PossessedTank = Cast<ATank>(InPawn);
    
    if (!ensure(PossessedTank)) { return; }
    
    // TODO: subscribe our local method to tank's death event
    PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
  }
}

void ATankPlayerController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  AimTowardsCrossHair();
}

void ATankPlayerController::AimTowardsCrossHair()
{
  if (!GetPawn()) { return; }
  auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
  if (!ensure(AimingComponent)) { return; }
  
  FVector HitLocation; // Out parameter
  
  // Get world location through crosshair (linetrace)
  bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
  if(bGotHitLocation) {
    // If it hits landscape/enemy
    // tell controlled tank to aim at this point
    AimingComponent->AimAt(HitLocation);
  }
  
  
}


bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
  // Find the crosshair position
  int32 ViewportSizeX, ViewportSizeY;
  GetViewportSize(ViewportSizeX, ViewportSizeY);
  FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
  //UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString())
  
  
  // Deproject the screen position of the cross to a world direction
  auto CameraWorldLocation = FVector();
  auto LookDirection = FVector();
  if (GetLookDirection(ScreenLocation, LookDirection)) {
    // Line trace to see what we hit (up to max range)
    return GetLookVectorHitLocation(LookDirection, HitLocation);
  }
  return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
  auto CameraWorldLocation = FVector();
  return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
  FHitResult HitResult;
  auto StartLocation = PlayerCameraManager->GetCameraLocation();
  auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
  
  if (GetWorld()->LineTraceSingleByChannel(
                                           HitResult,
                                           StartLocation,
                                           EndLocation, ECollisionChannel::ECC_Visibility
                                           )
    )
  {
    HitLocation = HitResult.Location;
    return true;
  }
  
  return false;
}


void ATankPlayerController::OnPossessedTankDeath()
{
  UE_LOG(LogTemp, Warning, TEXT("Player Controller OnTankDeath"))
  StartSpectatingOnly();
}
