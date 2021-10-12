// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankPlayerController.h"


// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay(); // construct base's constructor's stuff first

    //Debug lines
    /*
    auto ControlledTank = GetControlledTank();  //auto keyword is saying that ControlledTank variable is the type being initialized which is ATank*
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController is not possessing a tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController is possessing %s"), *(ControlledTank->GetName()));
    }
    */
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //Debugging
    //UE_LOG(LogTemp, Warning, TEXT("PlayerController's tick function is ticking....."));

    AimTowardsCrosshair();
    

}


//return the pawn that PlayerContrller is currently possessing (type cased into ATank)
ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank> (GetPawn()); 
    
}

// Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank())  
    {
        return;
    }

   FVector HitLocation;   //Out parameter so their values will be assigned by fuction after being passed by reference
   if (GetSightRayHitLocation(HitLocation))
   {
       // tell controlled tank to aim at this point.
       GetControlledTank()->AimAt(HitLocation);
   }

}

// Function with parameters passed by reference (out parameters) to get the hit location of world
// Get world location of your line trace through crosshair.
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{

    // First, find Crosshair position in term of pixel coordinates regardless of screen size variations

    // Get viewport size/screen size (also good if player change screen size and we still know crosshair position related to screen size)
    int32 ViewportSizeX, ViewportSizeY; // to store the size of current viewport (out parameters)
    GetViewportSize(ViewportSizeX, ViewportSizeY);  // passed by reference
    // Find crosshair coordinate in pixels values (2 float values specifying pixel coordinate to deproject later)
    // we can calculate those two float values directly in the constructor of FVector2D (eg. 50% * 1920 pixels and 33.333% * 1080 pixels)
    FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);   
    //UE_LOG(LogTemp, Warning, TEXT("Crosshair coordinates on screen in pixel values : %s"), *ScreenLocation.ToString());



    // Getting the direction the crosshair is looking. It means getting a Unit Vector whose direction is from camera toward crosshair
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        //UE_LOG(LogTemp, Warning, TEXT("Look direction of crosshair in pixel values : %s"), *LookDirection.ToString());
        
        // Line trace along that look direction and see what we hit up to max range
        if (GetLookVectorHitLocation(LookDirection, HitLocation))
        {
            //log the location of the object the ray hit
            //UE_LOG(LogTemp, Warning, TEXT("The location of the object hit by crosshair : %s"), *HitLocation.ToString());

            
        }
        else
        {
            //UE_LOG(LogTemp, Warning, TEXT("Invalid target by crosshair : %s"), *HitLocation.ToString());
        }

    }
    
    return true;

    // return false; // ray doesn't hit anything
}

// Line trace along that look direction and see what we hit up to max range
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
        
    if ( GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
        ECollisionChannel::ECC_Visibility)
        )
    {
        HitLocation = HitResult.Location;   //the way to get location vector from FHitResult or the location of the object that is hit
        return true;  // ray hit something
    }
    HitLocation = FVector(0);   // if nothing is hit, set the location to 0
    return false;     // ray doesn't hit anything e.g skybox is not part of the channel.
}


// Deproject the screen position of the crosshair to a world direction (to get Look Direction in Unit vector toward crosshair)
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation;  // Temp variable that we don't need but function needs it
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}


