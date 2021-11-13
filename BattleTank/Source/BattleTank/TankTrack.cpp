// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "SpawnPoint.h"
#include "SprungWheel.h"


UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
}

/*void UTankTrack::BeginPlay()
{
    Super::BeginPlay(); // construct base's constructor's stuff first

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

}*/

/*void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}*/


// this function will be called by Input Axis (Left or Right Track) Throttle nodes from blueprint
// Set a throttle between -1 and +1
void UTankTrack::SetThrottle(float Throttle)
{
    //CurrentThrottle = FMath::Clamp<float>((CurrentThrottle + Throttle), -1, 1);
    float CurrentThrottle = Throttle;
    DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
    /*auto Name = GetName();  // FString
    UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle);
    */

    // TODO Clamp Throttle values between min and max (-1 and +1) so that payer can't over-ride
    //auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    float ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
    /*auto ForceLocation = GetComponentLocation();  //locatio of the track
    auto TankRoot = Cast<UPrimitiveComponent> (GetOwner()->GetRootComponent());  //returns USceneComponent's pointer type casted as UPrimitiveComponent
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
    */

    TArray<ASprungWheel*> Wheels = GetWheels();
    float ForcePerWheel = ForceApplied / Wheels.Num();
    for (ASprungWheel* Wheel : Wheels)
    {
        Wheel->AddDrivingForce(ForcePerWheel);
    }
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
    TArray<ASprungWheel*> ResultArray;
    // out parameter
    TArray<USceneComponent*> Children;
    GetChildrenComponents(true, Children);

    for (USceneComponent* Child : Children)
    {
        USpawnPoint* SpawnPointChild = Cast<USpawnPoint> (Child);
        if(!SpawnPointChild) continue;

        AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
        ASprungWheel* SprungWheel = Cast<ASprungWheel> (SpawnedChild);
        if (!SprungWheel) continue;

        ResultArray.Add(SprungWheel);
    }

    return ResultArray;
}

/*void UTankTrack::ApplySidewaysForce()
{
    //calculate slipping speedd
    float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

    //work out the required accelation (v/t) needed in this frame to counter the slipping
    float DeltaTime = GetWorld()->GetDeltaSeconds();
    FVector CorrectionAcceleration = (SlippageSpeed / DeltaTime) * GetRightVector() * -1.0f;

    //calculate and apply sideway force/friction (F = m x a)
    UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent> (GetOwner()->GetRootComponent());
    FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;  //because we have 2 tracks
    TankRoot->AddForce(CorrectionForce);
}
*/

//checking if tracks are hitting/toughing the ground. we will only apply force if tank is on ground
/*void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    //UE_LOG(LogTemp, Warning, TEXT("%s Track is being hit!"), *GetOwner()->GetName());
    DriveTrack();
    ApplySidewaysForce();

    //reset throttle
    CurrentThrottle = 0;

}*/