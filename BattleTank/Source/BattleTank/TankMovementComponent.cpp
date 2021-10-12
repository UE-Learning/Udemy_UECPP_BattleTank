// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;

}


void UTankMovementComponent::IntendMoveForward(float Throw)
{

    /*UE_LOG(LogTemp, Warning, TEXT("Intend move forward's throw: %f"), Throw);*/
    if(!LeftTrack || !RightTrack)
    {
        return;
    }

    //move according to the throw value by calling Track's SetThrottle function
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);

    //TODO prevent double speed due to dual control use
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{

    /*UE_LOG(LogTemp, Warning, TEXT("Intend turn right's throw: %f"), Throw);*/
    if(!LeftTrack || !RightTrack)
    {
        return;
    }

    //move according to the throw value by calling Track's SetThrottle function
    LeftTrack->SetThrottle(2 * Throw);
    RightTrack->SetThrottle(-2 * Throw);

    //TODO prevent double speed due to dual control use
}
