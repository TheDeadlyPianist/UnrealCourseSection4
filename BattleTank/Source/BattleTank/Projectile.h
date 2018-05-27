// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

class URadialForceComponent;
class UParticleSystemComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void launchProjectile(float speed);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
		UStaticMeshComponent* collisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Particles)
		UParticleSystemComponent* launchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Particles)
		UParticleSystemComponent* collisionBlast = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float projectileDamage = 27;

private:
	UProjectileMovementComponent* projectileMovement = nullptr;

	UPROPERTY(EditAnywhere, Category = Firing)
		URadialForceComponent* radialForce = nullptr;

	UFUNCTION()
		void OnHit(AActor* HitActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	void onTimerExpire() {
		Destroy();
	}
};
