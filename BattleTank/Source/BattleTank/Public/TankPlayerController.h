// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"

// Must be last include:
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:

  UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
  void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

public:
  void BeginPlay() override;
  virtual void Tick(float DeltaTime) override;
  
  UPROPERTY(EditDefaultsOnly)
  float CrossHairXLocation = 0.5;
  
  UPROPERTY(EditDefaultsOnly)
  float CrossHairYLocation = 0.3333;
  
  UPROPERTY(EditDefaultsOnly)
  float LineTraceRange = 1000000; // 10km
  
private:  
  // Start moving the barrel so that it would shoot where the crosshair
  // intersects the world
  void AimTowardsCrossHair();
  
  
  bool GetSightRayHitLocation(FVector &OutHitLocation) const;
  bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
  bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
