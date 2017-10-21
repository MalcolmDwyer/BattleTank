// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

  
public:
  virtual void BeginPlay() override;
  void AimAt(FVector HitLocation);
  
  UFUNCTION(BlueprintCallable)
  void Fire();
  
  // TODO: remove once firing is moved to Aiming Component
  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float LaunchSpeed = 6000.0f; // 1000 m/s

protected:
  UPROPERTY(BlueprintReadOnly)
  UTankAimingComponent* TankAimingComponent = nullptr;
  
  
private:
	// Sets default values for this pawn's properties
	ATank();
  
  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  TSubclassOf<AProjectile> ProjectileBlueprint;

  UTankBarrel* Barrel = nullptr; // TODO Remove
  
  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float ReloadTimeInSeconds = 3.0f;
  
  double LastFireTime = 0;
};
