// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;   // Forward declaration

// Tank Aiming Component class object which is a member variable of Tank class  (we can see this comment in BP editor)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference (UTankBarrel* BarrelToSet);

public:	

	// Aim at the location represented by FVector parameter
	void AimAt(FVector HitLocation, float LaunchSpeed);

private:

	// Reference for Barrel which is a UStaticMeshComponent
	UTankBarrel* Barrel = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
		
};
