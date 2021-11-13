// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class ASprungWheel;


/**
 * Tank Track C++ class which inherits from UStaticMeshComponent. TankTrack is used to set maximum driving force and to apply it to the tank
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	
	UTankTrack();

	//virtual void BeginPlay() override;

	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);    // this function will be called by Input Axis nodes from blueprint
	void DriveTrack(float CurrentThrottle);

	//void ApplySidewaysForce();

	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000;  // sensible initial values in 400,000 Newton (F = m x a), mass is 40 tons, aceleration is 1g or 10ms-2
	
private:

	//UFUNCTION()
	//void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	//float CurrentThrottle = 0;
	
	TArray<ASprungWheel*> GetWheels() const;


};
