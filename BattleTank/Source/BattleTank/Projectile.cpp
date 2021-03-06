// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->SetupAttachment(CollisionMesh);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent> (FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->SetupAttachment(CollisionMesh);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->SetupAttachment(CollisionMesh);



}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	
}


void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    //UE_LOG(LogTemp, Warning, TEXT("%s Track is being hit!"), *GetOwner()->GetName());
    
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();

	ExplosionForce->FireImpulse();

	SetRootComponent(ImpactBlast);  // we don't want to destroy root CollisionMesh so we change root
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		GetActorLocation(),  // Origin of damage
		ExplosionForce->Radius,  // radial force component (ExplosionForce)'s radius value from BP (1000)
		UDamageType::StaticClass(),
		TArray<AActor*> ()  // array of actors that will receive damage, here, this means it will damage all actors.
	);

	FTimerHandle Timer; //outparameter
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, DestroyDelay, false);

}

void AProjectile::OnTimerExpire()
{
	Destroy();
}



/*
// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

// will be called from Tank class's Fire function using Projectile object spawned by SpawnActor.
void AProjectile::LaunchProjectile(float Speed)
{
	//float Time = GetWorld()->GetTimeSeconds();       // to make sure this method is ticking (called from Tick function)
	//UE_LOG(LogTemp, Warning, TEXT("At time %f, Tank has fired projectile with %f speed"), Time, Speed);

	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}

