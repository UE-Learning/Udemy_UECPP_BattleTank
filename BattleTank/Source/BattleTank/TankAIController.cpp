// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank> (GetPawn()); //return the pawn that AIContrller is currently possessing (type cased into ATank)
    
}

void ATankAIController::BeginPlay()
{
    Super::BeginPlay(); // construct base's constructor's stuff first

    //Debug lines
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
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AI controller found player tank : %s"), *(PlayerTank->GetName()));
    }

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