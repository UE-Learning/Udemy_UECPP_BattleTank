// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * Tank Turret C++ class which inherits from UStaticMeshComponent
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), hidecategories = ("Collision") )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	public:
		void Rotate (float RelativeSpeed);
	
	private:
		UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxDegreesPerSecond = 50;  // 50 is sensible initial values to be changed in UE editor
};
