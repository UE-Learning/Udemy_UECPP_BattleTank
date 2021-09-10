// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

	public: 
		ATank* GetControlledTank() const;
		void BeginPlay() override;   //overriding AActor's BeginPlay to add debug function in BeginPlay()

		ATank* GetPlayerTank() const;  //to get the pawn (ATank) possessed by ATankPlayerController
	
};
