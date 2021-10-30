// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
    Super::BeginPlay(); // construct base's constructor's stuff first
	LastFireTime = FPlatformTime::Seconds();  // so that first fire is after initial reload

}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//UE_LOG(LogTemp, Warning, TEXT("Aiming Component is ticking"));
	if(RoundsLeft <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else 
	{
		FiringState = EFiringState::Locked;
	}
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	float Tolerance = 0.01;
	if (!ensure(Barrel))
	{
		return false;
	}
	return (!Barrel->GetForwardVector().Equals(AimDirection, Tolerance));
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Need public function to set value of private member variable.
/*void UTankAimingComponent::SetBarrelReference (UTankBarrel* BarrelToSet)
{
	if(!BarrelToSet)
	{
		return;
	}
	Barrel = BarrelToSet;
}


// Need public function to set value of private member variable.
void UTankAimingComponent::SetTurretReference (UTankTurret* TurretToSet)
{
	if(!TurretToSet)
	{
		return;
	}
	Turret = TurretToSet;
}*/

// Aim at the location represented by FVector parameter
void UTankAimingComponent::AimAt(FVector HitLocation)
{
	/*
	FString ThisTankName = GetOwner()->GetName();
	FVector BarrelLocation = Barrel->GetComponentLocation();
	UE_LOG(LogTemp, Warning, TEXT("%s is aiming at : %s from %s with %f speed"), *ThisTankName, *HitLocation.ToString(), *BarrelLocation.ToString(), LaunchSpeed);
	*/

	if (!ensure(Barrel))  // protect from null pointer error
	{
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Call SuggestProjectileVelocity function to get OutLaunchVelocity (the direction for the barrel to aim at).
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false, 0.0f, 0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();   // GetSafeNormal return a unit vector
		/*
		FString ThisTankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *ThisTankName, *AimDirection.ToString());
		*/
		/*
		float Time = GetWorld()->GetTimeSeconds();       // to make sure this method is ticking (called from Tick function)
    	UE_LOG(LogTemp, Warning, TEXT("At time %f, Aim solution found"), Time);
		*/

		MoveBarrelTowards();

	}
	/*
	else
	{
		
		// eg. aiming at too far away mountain, given launch speed won't reach it, so SuggestProjectileVelocity will return false for player tank (AI tank will return true due to player within reach of projectile)
		float Time = GetWorld()->GetTimeSeconds();       // to make sure this method is ticking (called from Tick function)
		UE_LOG(LogTemp, Warning, TEXT("At time %f, No aim solution found"), Time);   
		
	}
	*/
}

// it also moves turret
void UTankAimingComponent::MoveBarrelTowards()
{
	if (!ensure(Barrel) || !ensure(Turret))
	{
		return;
	}
	// Calculate difference between current barrel rotation and AimDirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();  // get current rotational values
	FRotator AimAsRotator = AimDirection.Rotation();  // this will be the destination rotational values
	FRotator DeltaRotator = AimAsRotator - BarrelRotator; // difference between current and final rotational values

	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch);

	if(FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel))   // null pointer logic error
	{
		return;
	}
	
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
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
		RoundsLeft--;
	}
}
