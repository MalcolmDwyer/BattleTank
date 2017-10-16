// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
  if (!BarrelToSet) { return; }
  Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
  if (!TurretToSet) { return; }
  Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
  auto OurTankName = GetOwner()->GetName();
  if (!Barrel) { return; }
  if (!Turret) { return; }
  
  auto BarrelLocation = Barrel->GetComponentLocation();
  
  
  FVector OutLaunchVelocity;
  FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
  
  // Calculate the OutLaunchVelocity
  bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
                                                                      this,
                                                                      OutLaunchVelocity,
                                                                      StartLocation,
                                                                      HitLocation,
                                                                      LaunchSpeed,
                                                                      false,
                                                                      0.f,
                                                                      0.f,
                                                                      ESuggestProjVelocityTraceOption::DoNotTrace
                                                                      );
  
  if (bHaveAimSolution) {
    auto AimDirection = OutLaunchVelocity.GetSafeNormal();
//    UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *OurTankName, *AimDirection.ToString())
    MoveBarrelTowards(AimDirection);
    auto Time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time)
  }
  else {
    auto Time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f: AimingComponent - no solution."), Time)
  }
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
  if (!Barrel) { return; }
  if (!Turret) { return; }
  
  // Transform AimDirection based on rotation of entire tank
  // Rotate turret gimbal to corresponding to X,Y components
  // Elevate turret to corresponding Z component.
  
  auto BarrelRotator = Barrel->GetForwardVector().Rotation();
  auto AimAsRotator = AimDirection.Rotation();
  auto DeltaRotator = AimAsRotator - BarrelRotator;
//  UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString())
  
  Barrel->Elevate(DeltaRotator.Pitch);
  Turret->Rotate(DeltaRotator.Yaw);
}

