// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
  Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
  auto OurTankName = GetOwner()->GetName();
  if (!Barrel) { return; }
  
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
                                                                      ESuggestProjVelocityTraceOption::DoNotTrace
                                                                      );
  
  if (bHaveAimSolution) {
    auto AimDirection = OutLaunchVelocity.GetSafeNormal();
    UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *OurTankName, *AimDirection.ToString())
    MoveBarrel(AimDirection);
  }
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
  // Transform AimDirection based on rotation of entire tank
  // Rotate turret gimbal to corresponding to X,Y components
  // Elevate turret to corresponding Z component.
}

