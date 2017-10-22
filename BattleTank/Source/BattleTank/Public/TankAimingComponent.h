// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
  Reloading,
  Aiming,
  Locked
};

// Forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
  
  virtual void BeginPlay() override;

  
  virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
  
  UFUNCTION(BlueprintCallable, Category = "Setup")
  void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

  void AimAt(FVector HitLocation);
  
  UFUNCTION(BlueprintCallable, Category = "Firing")
  void Fire();
  
  EFiringState GetFiringState() const;
  
protected:
  UPROPERTY(BlueprintReadonly, Category = "State")
  EFiringState FiringState = EFiringState::Reloading;
  
  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float LaunchSpeed = 6000.0f; // 1000 m/s
  
  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  TSubclassOf<AProjectile> ProjectileBlueprint;


private:
  UTankBarrel* Barrel = nullptr;
  UTankTurret* Turret = nullptr;
  
  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float ReloadTimeInSeconds = 3.0f;
  
  double LastFireTime = 0;

  void MoveBarrelTowards();
  bool IsBarrelMoving();
  FVector AimDirection = FVector(0);
  
};
