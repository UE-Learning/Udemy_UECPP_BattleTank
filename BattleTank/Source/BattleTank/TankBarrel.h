// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


// Tank Barrel is a member object of TankAimingComponent class (we can see this comment in BP editor)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), hidecategories = ("Collision") )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

	public:
		void Elevate(float RelativeSpeed);  // -1 is max downward spd, +1 is max upward spd
	
	private:
		UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 10;  // 10 is sensible initial values to be changed in UE editor

		UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDegrees = 40;

		UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegrees = 0;


};
