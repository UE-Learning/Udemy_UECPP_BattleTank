// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;   // Forward declaration
class UTankTurret;   // Forward declaration
class AProjectile;   // Forward declaration

// enum variable type for storing different firing readiness state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};


// Tank Aiming Component class object which is a member variable of Tank class  (we can see this comment in BP editor)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	/*void SetBarrelReference (UTankBarrel* BarrelToSet);

	void SetTurretReference (UTankTurret* TurretToSet);*/

	// Aim at the location represented by FVector parameter
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	bool IsBarrelMoving();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:

	
	void MoveBarrelTowards(); //it also moves turret

	void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	// Reference for Barrel which used to be a UStaticMeshComponent but now a UTankBarrel object pointer
	UTankBarrel* Barrel = nullptr;

	// Reference for Turret which used to be a UStaticMeshComponent
	UTankTurret* Turret = nullptr;

	FVector AimDirection;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000;  // sensible starting value of 40 m/s (if value is too large, projectile can reach everywhere removing the need to move tank)

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 3;  // 3 sec reload time, can't fire more than once in 3 seconds

	double LastFireTime = 0;  // initialized as 0 sec, reassign with current time after firing

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;
		
};
