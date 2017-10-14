// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"


// Must be last include:
#include "TankPlayerController.generated.h"

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
  
private:
  ATank* ControlledTank;
  
  // Start moving the barrel so that it would shoot where the crosshair
  // intersects the world
  void AimTowardsCrossHair();
  
  
  bool GetSightRayHitLocation(FVector &OutHitLocation) const;
};


