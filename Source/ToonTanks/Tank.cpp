// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATank::ATank()
{
  // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
  SpringArm->SetupAttachment(RootComponent);

  Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
  Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
  Super::BeginPlay();

  TankPlayerController = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  HandleAim();
}

void ATank::HandleDestruction()
{
  Super::HandleDestruction();

  // specific for tank
  SetActorHiddenInGame(true);
  SetActorTickEnabled(false);
}

void ATank::HandleAim()
{
  if (TankPlayerController)
  {
    FHitResult HitResult;
    const bool HasHit = TankPlayerController->GetHitResultUnderCursor(
        ECollisionChannel::ECC_Visibility,
        false,
        HitResult);
    if (HasHit)
    {
      FVector HitPoint = HitResult.ImpactPoint;
      // DrawDebugSphere(
      //     GetWorld(),
      //     HitPoint,
      //     20,
      //     10,
      //     FColor::Red,
      //     false,
      //     -1.f,
      //     0U,
      //     2);

      RotateTurret(HitPoint);
    }
  }
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
  PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

  PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value)
{
  FVector DeltaLocation(0.f);
  double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

  DeltaLocation.X = Value * Speed * DeltaTime;

  AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
  FRotator DeltaRotation(0.f);
  double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

  DeltaRotation.Yaw = Value * DeltaTime * TurnSpeed;
  AddActorLocalRotation(DeltaRotation);
}
