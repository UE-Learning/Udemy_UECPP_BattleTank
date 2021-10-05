// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    //float Time = GetWorld()->GetTimeSeconds();       // to make sure this method is ticking (called from Tick function)
    //UE_LOG(LogTemp, Warning, TEXT("Barrel's Elevate method called with speed %f at time %f "), RelativeSpeed, Time);



    // Move barrel in the right amount per one frame
    // Given a max elevation speed to limit the barrel movement (Barrel class), and frame time (frame independent)
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
    float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    float RawNewElevation = USceneComponent::GetRelativeRotation().Pitch + ElevationChange;
    float Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
    SetRelativeRotation(FRotator(Elevation, 0, 0));

}