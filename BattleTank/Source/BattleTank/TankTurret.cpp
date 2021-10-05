// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
    float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    float Rotation = USceneComponent::GetRelativeRotation().Yaw + RotationChange;
    SetRelativeRotation(FRotator(0, Rotation, 0));

}

