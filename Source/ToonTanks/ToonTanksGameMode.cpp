// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::BeginPlay()
{
  Super::BeginPlay();

  HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
  // UE_LOG(LogTemp, Warning, TEXT("Actor Died (Game Mode)"));
  if (DeadActor == Tank)
  {
    Tank->HandleDestruction();

    if (Tank->GetTankPlayerController())
    {
      ToonTanksPlayerController->SetPlayerEnabledState(false);
      GameOver(false);
      MyBluprintFunctionWow(true, 32);
    }
  }

  else if (ATower *DestroyedTower = Cast<ATower>(DeadActor)) // can declare local variable here in condition
  {
    DestroyedTower->HandleDestruction();
    TargetTowers--;
    // UE_LOG(LogTemp, Warning, TEXT("remaining: %i"), TargetTowers);
    if (TargetTowers == 0)
    {
      GameOver(true);
    }
  }
}

void AToonTanksGameMode::HandleGameStart()
{
  TargetTowers = GetTargetTowerCount();
  Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
  ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

  StartGame();

  if (ToonTanksPlayerController)
  {
    ToonTanksPlayerController->SetPlayerEnabledState(false);

    // create the timer callback
    FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(
        ToonTanksPlayerController,
        &AToonTanksPlayerController::SetPlayerEnabledState,
        true); // the 3rd input and so on will be the parameter argument of the callback function

    // the timer handle
    FTimerHandle PlayerEnableTimerHandle;

    GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, TimerDelegate, StartDelay, false);
  }
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
  TArray<AActor *> Towers;
  UGameplayStatics::GetAllActorsOfClass(
      this,
      ATower::StaticClass(),
      Towers);

  return Towers.Num();
}
