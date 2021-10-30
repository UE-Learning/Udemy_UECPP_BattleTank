// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "TankAIController.generated.h"


/*class ATank;  // Forward declaration*/

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

	private: 
		
		virtual void BeginPlay() override;   //overriding AActor's BeginPlay to add debug function in BeginPlay()

		// Called every frame
		virtual void Tick(float DeltaTime) override;

		// How close AI tank can get near player
		//UPROPERTY(EditAnywhere)
		float AcceptanceRadius = 6000;  // check if it is in cm

		/*
		ATank* GetPlayerTank() const;  //to get the pawn (ATank) possessed by ATankPlayerController
		ATank* GetControlledTank() const;
		*/
	
};
