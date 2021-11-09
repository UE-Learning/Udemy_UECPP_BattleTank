// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"    //put new includes above

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

/*class UTankBarrel;  // Forward declaration
class UTankAimingComponent;  // Forward declaration which allows us to include header file in .cpp file instead of here in .h file
class UTankTurret;  // Forward declaration
class AProjectile;  // Forward declaration */

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;
	
	// Called to bind functionality to input
	/*virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	*/

	// Variables
	/*UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000;  // sensible starting value of 40 m/s (if value is too large, projectile can reach everywhere removing the need to move tank)
	*/

	/*UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;
	// UClass* ProjectileBlueprint;    // alternative to TSubclassOf <>

	UTankBarrel* Barrel = nullptr;  // Local Barrel reference for spawning projectile  // TODO remove it

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 3;  // 3 sec reload time, can't fire more than once in 3 seconds

	double LastFireTime = 0;  // initialized as 0 sec, reassign with current time after firing */


protected:
	/*UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;*/

	//UPROPERTY(BlueprintReadOnly)
	/*UTankMovementComponent* TankMovementComponent = nullptr;*/

	// Called when the game starts or when spawned
	/*virtual void BeginPlay() override;*/

public:
	// Sets default values for this pawn's properties
	ATank();  //a constructor

	virtual void BeginPlay() override;

	FTankDelegate OnDeath;

	// Pass Tank's component barrel reference to set subobject's member variable with it
	// We also want to expose this func to blueprint editor so that the child (Tank_BP) can use it to set up static mesh object's reference
	/*UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBarrelReference(UTankBarrel* BarrelToSet);


	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetTurretReference(UTankTurret* TurretToSet);*/

	// Aim at (either the object through crossair or player)
	/*void AimAt(FVector HitLocation);*/

	/*UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();*/

	
	// call by engine when actor damage is dealt.
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// return the current health as a percentage of starting health between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

};
