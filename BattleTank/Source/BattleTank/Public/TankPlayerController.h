// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"


// Must be last include:
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
  ATank* GetControlledTank() const;
  
  void BeginPlay() override;
  virtual void Tick(float DeltaTime) override;
  
  UPROPERTY(EditDefaultsOnly)
  float CrossHairXLocation = 0.5;
  
  UPROPERTY(EditDefaultsOnly)
  float CrossHairYLocation = 0.3333;
  
  UPROPERTY(EditDefaultsOnly)
  float LineTraceRange = 1000000; // 10km
  
private:
  ATank* ControlledTank;
  
  // Start moving the barrel so that it would shoot where the crosshair
  // intersects the world
  void AimTowardsCrossHair();
  
  
  bool GetSightRayHitLocation(FVector &OutHitLocation) const;
  bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
  bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
