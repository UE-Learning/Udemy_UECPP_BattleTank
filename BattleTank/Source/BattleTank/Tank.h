// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"    //put new includes above

class UTankBarrel;  // Forward declaration
class UTankAimingComponent;  // Forward declaration which allows us to include header file in .cpp file instead of here in .h file

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();  //a constructor

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	

	// Variables
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000;  // sensible starting value of 1000 m/s, TODO: find better launch speed and edit in UE


protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Aim at (either the object through crossair or player)
	void AimAt(FVector HitLocation);

	// Pass Tank's component barrel reference to set subobject's member variable with it
	// We also want to expose this func to blueprint editor so that the child (Tank_BP) can use it to set up static mesh object's reference
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);


};