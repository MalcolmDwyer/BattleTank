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
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
  if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
    FiringState = EFiringState::Reloading;
  }
  else if (IsBarrelMoving()) {
    FiringState = EFiringState::Aiming;
  }
  else {
    FiringState = EFiringState::Locked;
  }
}

EFiringState UTankAimingComponent::GetFiringState() const
{
  return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving()
{
  if (!ensure(Barrel)) { return false; }
  auto BarrelForward = Barrel->GetForwardVector();
  return !AimDirection.Equals(BarrelForward, 0.01);
}

void UTankAimingComponent::BeginPlay()
{
  Super::BeginPlay();
  LastFireTime = FPlatformTime::Seconds();
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
    AimDirection = OutLaunchVelocity.GetSafeNormal();
    MoveBarrelTowards();
  }
}

void UTankAimingComponent::MoveBarrelTowards()
{
  if (!ensure(Barrel)) { return; }
  if (!ensure(Turret)) { return; }
  
  // Transform AimDirection based on rotation of entire tank
  // Rotate turret gimbal to corresponding to X,Y components
  // Elevate turret to corresponding Z component.
  
  auto BarrelRotator = Barrel->GetForwardVector().Rotation();
  auto AimAsRotator = AimDirection.Rotation();
  auto DeltaRotator = AimAsRotator - BarrelRotator;
  
  Barrel->Elevate(DeltaRotator.Pitch);
  
  Turret->Rotate(
    ((FMath::Abs(DeltaRotator.Yaw) > 180.0) ? -1 : 1) * DeltaRotator.Yaw
  );
  
  
}



void UTankAimingComponent::Fire()
{
  
  if (FiringState != EFiringState::Reloading) {
  
    if (!ensure(Barrel)) { return; }
    if (!ensure(ProjectileBlueprint)) { return; }

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

