// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"


// this function will be called by Input Axis (Left or Right Track) Throttle nodes from blueprint
// Set a throttle between -1 and +1
void UTankTrack::SetThrottle(float Throttle)
{
    auto Name = GetName();  // FString
    UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle);

    // TODO Clamp Throttle values between min and max (-1 and +1) so that payer can't over-ride
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();  //locatio of the track
    auto TankRoot = Cast<UPrimitiveComponent> (GetOwner()->GetRootComponent());  //returns USceneComponent's pointer type casted as UPrimitiveComponent
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}
