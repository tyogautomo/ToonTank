// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float InitialSpeed = 1000;

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 2000;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent *ProjectileMesh;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent *ProjectileMovementComponent;

	UFUNCTION()
	void OnHit(
			UPrimitiveComponent *HitComp,
			AActor *OtherActor,
			UPrimitiveComponent *OtherComp,
			FVector NormalImpulse,
			const FHitResult &Hit);

	UPROPERTY(EditAnywhere)
	float Damage = 50;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem *HitParticle;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystemComponent *TrailParticle;
};
