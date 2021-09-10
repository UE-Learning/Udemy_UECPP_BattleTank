// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"


// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay(); // construct base's constructor's stuff first

    //Debug lines
    auto ControlledTank = GetControlledTank();  //auto keyword is saying that ControlledTank variable is the type being initialized which is ATank*
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController is not possessing a tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController is possessing %s"), *(ControlledTank->GetName()));
    }
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //Debugging
    //UE_LOG(LogTemp, Warning, TEXT("PlayerController's tick function is ticking....."));

    //AimTowardsCrosshair();
    

}


ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank> (GetPawn()); //return the pawn that PlayerContrller is currently possessing (type cased into ATank)
    
}

// Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank())
    {
        return;
    }

    //psesudo codes
    /*
        Get world location if you line trace through crosshair.
        If it hits the landscape, tell controlled tank to aim at this point.
    */
}
