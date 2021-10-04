// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    // Move barrel in the right amount per one frame
    //float Time = GetWorld()->GetTimeSeconds();       // to make sure this method is ticking (called from Tick function)
    //UE_LOG(LogTemp, Warning, TEXT("Barrel's Elevate method called with speed %f at time %f "), RelativeSpeed, Time);


    // Given a max elevation speed to limit the barrel movement (Barrel class), and frame time (frame independent)

}