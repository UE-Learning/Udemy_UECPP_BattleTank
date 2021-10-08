// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Constructing subobject (member variable) of UTankAimingComponent during construction of owning class (ATank)
	// no need to protect the pointer as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent> (FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ATank::AimAt(FVector HitLocation)
{
	// Delagating the actual aiming job to subobject's function
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);

	
}


// Pass Tank's component barrel reference to set subobject's member variable with it
// We also want to expose this func to blueprint editor so that the child (Tank_BP) can use it to set up static mesh object's reference
void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);

	Barrel = BarrelToSet;  // for spawning projectile
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}


void ATank::Fire()
{
	bool bIsReloaded = true;
	bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	
	if (Barrel && bIsReloaded)
	{
		// Spawn a projectile at sotcket location on the barrel
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),  // Projectile is the socket name on barrel
				Barrel->GetSocketRotation(FName("Projectile"))
		);

		// launch the projectile with given speed
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

