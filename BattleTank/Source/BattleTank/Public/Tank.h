// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
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
  
  UFUNCTION(BlueprintCallable, Category = Setup)
  void SetBarrelReference(UTankBarrel* BarrelToSet);
  
  UFUNCTION(BlueprintCallable, Category = Setup)
  void SetTurretReference(UTankTurret* TurretToSet);
  
  UPROPERTY(EditDefaultsOnly, Category = Firing)
  float LaunchSpeed = 6000.0f; // 1000 m/s

protected:
  UPROPERTY(BlueprintReadOnly)
  UTankAimingComponent* TankAimingComponent = nullptr;
  
  UPROPERTY(BlueprintReadOnly)
  UTankMovementComponent* TankMovementComponent = nullptr;
  
private:
	// Sets default values for this pawn's properties
	ATank();
  
  UPROPERTY(EditDefaultsOnly, Category = Setup)
  TSubclassOf<AProjectile> ProjectileBlueprint;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
  
  
  UTankBarrel* Barrel = nullptr;
  
  UPROPERTY(EditDefaultsOnly, Category = Firing)
  float ReloadTimeInSeconds = 3.0f;
  
  double LastFireTime = 0;
};
