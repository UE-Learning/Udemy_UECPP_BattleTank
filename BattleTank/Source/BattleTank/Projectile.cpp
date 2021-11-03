// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->SetupAttachment(CollisionMesh);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent> (FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// will be called from Tank class's Fire function using Projectile object spawned by SpawnActor.
void AProjectile::LaunchProjectile(float Speed)
{
	//float Time = GetWorld()->GetTimeSeconds();       // to make sure this method is ticking (called from Tick function)
	//UE_LOG(LogTemp, Warning, TEXT("At time %f, Tank has fired projectile with %f speed"), Time, Speed);

	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}

