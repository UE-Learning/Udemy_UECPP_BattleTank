// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/*class ATank;  // Forward declaration*/
class UTankAimingComponent;

/**
 *  Responsible for helping the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	private:
		UPROPERTY(EditAnywhere)             // Expose this variable to editor, can edit anywhere
		float CrossHairXLocation = 0.5;     // Crosshair is set up as 50% or midway in X-axis in PlayerUI_BP widget
		
		UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.33333; // Crosshair is set up as 33.33% or 1/3 in Y-axis in PlayerUI_BP widget

		UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.f;   // Maximum range of line trace for hit target (10km's equivalent value in cm).

	protected:
		UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent (UTankAimingComponent* AimCompRef);

		virtual void SetPawn(APawn* InPawn) override;
	
	public:
		
		void BeginPlay() override;   //overriding AActor's BeginPlay to add debug function in BeginPlay()

		// Called every frame
		virtual void Tick(float DeltaTime) override;

		/*UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank() const;*/

		// Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
		void AimTowardsCrosshair();

		// Function with parameters passed by reference (out parameters) to get the hit location of world, return true if it hit landscape
		bool GetSightRayHitLocation(FVector& HitLocation) const;

		// Deproject the screen position of the crosshair to a world direction (to get Look Direction of crosshair)
		bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

		// Line Tracing
		bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

		UFUNCTION()
		void OnPossessedTankDeath();

};
