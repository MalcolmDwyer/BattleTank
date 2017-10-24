// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:
  AProjectile();
  virtual void BeginPlay() override;
  virtual void Tick(float DeltaTime) override;
  void LaunchProjectile(float Speed);
 
private:
  UProjectileMovementComponent* ProjectileMovement = nullptr;
  
  UPROPERTY(VisibleAnywhere, Category = "Components")
  UStaticMeshComponent* CollisionMesh = nullptr;
  
  UPROPERTY(VisibleAnywhere, Category = "Components")
  UParticleSystemComponent* LaunchBlast = nullptr;
};
