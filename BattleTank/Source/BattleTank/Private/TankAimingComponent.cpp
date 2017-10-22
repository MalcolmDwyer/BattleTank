// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
  if (!BarrelToSet || !TurretToSet) { return; }
  Barrel = BarrelToSet;
  Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
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
    MoveBarrelTowards(AimDirection);
  }
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
  if (!Barrel || !Turret) { return; }
  
  // Transform AimDirection based on rotation of entire tank
  // Rotate turret gimbal to corresponding to X,Y components
  // Elevate turret to corresponding Z component.
  
  auto BarrelRotator = Barrel->GetForwardVector().Rotation();
  auto AimAsRotator = AimDirection.Rotation();
  auto DeltaRotator = AimAsRotator - BarrelRotator;
  
  Barrel->Elevate(DeltaRotator.Pitch);
  Turret->Rotate(DeltaRotator.Yaw);
}



void UTankAimingComponent::Fire()
{
  if (!ensure(Barrel && ProjectileBlueprint)) { return; }
  bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
  
  if (Barrel && isReloaded) {
    // Spawn a projectile at barrel location
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(
                                                          ProjectileBlueprint,
                                                          Barrel->GetSocketLocation(FName("Projectile")),
                                                          Barrel->GetSocketRotation(FName("Projectile"))
                                                          );
    
    Projectile->LaunchProjectile(LaunchSpeed);
    LastFireTime = FPlatformTime::Seconds();
  }
  
}

