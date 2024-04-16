// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components");
	class USpringArmComponent *SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components");
	class UCameraComponent *Camera;

	UPROPERTY(EditAnywhere, Category = "Movement");
	float Speed = 250;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = true));
	float TurnSpeed = 100;

	void Move(float Value);
	void Turn(float Value);

	APlayerController *TankPlayerController;

	void HandleAim();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	APlayerController *GetTankPlayerController() const { return TankPlayerController; }
};
