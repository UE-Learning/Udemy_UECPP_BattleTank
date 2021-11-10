// Fill out your copyright notice in the Description page of Project Settings.


/*#include "Tank.h"*/
#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h"
// Also Depends on Movement Component via AI NavMesh Pathfinding system


void ATankAIController::BeginPlay()
{
    Super::BeginPlay(); // construct base's constructor's stuff first

    //Debug lines
    /*
    auto ControlledTank = GetControlledTank();  //auto keyword is saying that ControlledTank variable is the type being initialized which is ATank*
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Controller is not possessing a tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Controller is possessing %s"), *(ControlledTank->GetName()));
    }
    
    ATank* PlayerTank = GetPlayerTank();
    if (!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI controller cannot find Player tank!"));
    }
    /*
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AI controller found player tank : %s"), *(PlayerTank->GetName()));
    }
    */

}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if (InPawn)
    {
        ATank* PossessedTank = Cast<ATank>(InPawn);
        if (!PossessedTank)
        {
            UE_LOG(LogTemp, Warning, TEXT("No Possessed Tank"));
            return;
        }

        // Subscribe to broadcast event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);

    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No Incoming Pawn"));
        return;
    }
}

// Delegate function that will handle broadcast event
void ATankAIController::OnPossessedTankDeath()
{
    //UE_LOG(LogTemp, Warning, TEXT("AI Tank died"));
    if (!GetPawn())
    {
        return;
    }
    GetPawn()->DetachFromControllerPendingDestroy();


}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Move towards player

    
    // tell controlled tank to aim at player.
    // don't forget to protect pointer by checking if there is a valid player tank
    APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    APawn* ControlledTank = GetPawn();
    UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
      
    //Note: we won't try to cast it before checking null pointer because the cast will fail if PlayerPawn is nullptr
    if (!ensure(PlayerTank && ControlledTank))
    {
        return;
    }
    if (!ensure(AimingComponent))
    {
        return;
    }
    
    // Move towards player
    MoveToActor(PlayerTank, AcceptanceRadius);

    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    
    // Fire if ready (checking the reloading time is done in Tank's Fire function. Otherwise, AI tank will fire every frame)
    /*ControlledTank->Fire();*/
    if (AimingComponent->GetFiringState() == EFiringState::Locked)
    {
        AimingComponent->Fire();
    }
}


/*
ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank> (GetPawn()); //return the pawn that AIContrller is currently possessing (type cased into ATank)
    
}


ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    //Note: we won't try to cast it before checking null pointer because the cast will fail if PlayerPawn is nullptr
    if (!PlayerPawn)
    {
        return nullptr;
    }

    return Cast<ATank> (PlayerPawn);
}
*/