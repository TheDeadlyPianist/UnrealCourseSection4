// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	massToAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WheelConstraints"));
	SetRootComponent(massToAxleConstraint);

	axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	axle->AttachToComponent(massToAxleConstraint, FAttachmentTransformRules::KeepRelativeTransform);

	axleToWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleConstraints"));
	axleToWheelConstraint->AttachToComponent(axle, FAttachmentTransformRules::KeepRelativeTransform);

	wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	wheel->AttachToComponent(axle, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	wheel->SetNotifyRigidBodyCollision(true);
	wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	SetConstraints();
}

void ASprungWheel::SetConstraints() {
	AActor* rootBody = GetAttachParentActor();
	if (!rootBody) return;
	UPrimitiveComponent* bodyRootComponent = Cast<UPrimitiveComponent>(rootBody->GetRootComponent());
	if (!bodyRootComponent) return;
	massToAxleConstraint->SetConstrainedComponents(bodyRootComponent, NAME_None, axle, NAME_None);
	axleToWheelConstraint->SetConstrainedComponents(axle, NAME_None, wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics) {
		totalForceThisFrame = 0;
	}
}

void ASprungWheel::addDrivingForce(float forceMagnitude) {
	totalForceThisFrame += forceMagnitude;
}

void ASprungWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit) {
	applyForce();
}

void ASprungWheel::applyForce() {
	wheel->AddForce(axle->GetForwardVector() * totalForceThisFrame);
}
