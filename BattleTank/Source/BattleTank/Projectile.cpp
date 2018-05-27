// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ProjectileMesh"));
	SetRootComponent(collisionMesh);
	collisionMesh->SetNotifyRigidBodyCollision(true);
	collisionMesh->SetVisibility(true);
	
	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlastParticleComponent"));
	launchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	collisionBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("CollisionBlastParticleComponent"));
	collisionBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	collisionBlast->bAutoActivate = false;

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileComponent"));
	projectileMovement->bAutoActivate = false;

	radialForce = CreateDefaultSubobject<URadialForceComponent>(FName("RadialForce"));
	radialForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::launchProjectile(float speed) {
	projectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	projectileMovement->Activate();
}

void AProjectile::OnHit(AActor* HitActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	launchBlast->Deactivate();
	collisionBlast->Activate();
	radialForce->FireImpulse();

	SetRootComponent(collisionBlast);
	collisionMesh->DestroyComponent();

	float minDamage = projectileDamage * 0.1;

	UGameplayStatics::ApplyRadialDamageWithFalloff(
		this,
		projectileDamage,
		minDamage,
		GetActorLocation(),
		0.f,
		1000.f,
		1.4f,
		UDamageType::StaticClass(),
		TArray<AActor*>(),
		this
	);

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AProjectile::onTimerExpire, 4.f);
}


