// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
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
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

