// Copyright OZ Ltd.


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
    if(!ensure(LeftTrack && RightTrack))
    {
        return;
    }

    //move according to the throw value by calling Track's SetThrottle function
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);

    //If you want to prevent doubling the Throw due to using both left stick and AD ZC keys, unbind the keyboard inputs

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{

    /*UE_LOG(LogTemp, Warning, TEXT("Intend turn right's throw: %f"), Throw);*/
    if(!ensure(LeftTrack && RightTrack))
    {
        return;
    }

    //move according to the throw value by calling Track's SetThrottle function
    LeftTrack->SetThrottle(2 * Throw);
    RightTrack->SetThrottle(-2 * Throw);

    //If you want to prevent doubling the Throw due to using both left stick and AD ZC keys, unbind the keyboard inputs
}


// overriding the virtual function of NavMovementComponent
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    // No need to call Super as we are replacing the functionality so that tanks use our movement physics

    FString TankName = GetOwner()->GetName();
    FVector AIForwardIntention = MoveVelocity.GetSafeNormal();   // the unit vector in the direction where AI want tank to move
    FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();  // the forward direction the tank is facing

    // Check how parallel the two vectors are and move forward if parallel, backward if they are 180 (opposite), don't move if perpendicular.
    float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
    IntendMoveForward(ForwardThrow);

    // Check how perpendicular the two vectors are and turn right if perpendicular 90 at max speed, turn left if 270, do nothing if parallel
    float RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
    IntendTurnRight(RightThrow);

    /*UE_LOG(LogTemp, Warning, TEXT("Tank %s is vectoring via Request Direct Move's MoveVelocity to : %s"), *TankName, *MoveVelocityString);*/

}
