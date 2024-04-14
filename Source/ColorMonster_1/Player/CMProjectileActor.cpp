// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CMProjectileActor.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ACMProjectileActor::ACMProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sphere Collision
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	CollisionComponent->InitSphereRadius(16.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &ACMProjectileActor::OnHit);
	RootComponent = CollisionComponent;

	// Static Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(CollisionComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/FPWeapon/Mesh/FirstPersonProjectileMesh.FirstPersonProjectileMesh'"));
	if (StaticMeshRef.Object)
	{
		StaticMesh->SetStaticMesh(StaticMeshRef.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CMPROJECTILEACTOR: Failed to Load Static Mesh"));
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialRef(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/FPWeapon/Materials/FirstPersonProjectileMaterial.FirstPersonProjectileMaterial'"));
	if (MaterialRef.Object)
	{
		StaticMesh->SetMaterial(0, MaterialRef.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CMPROJECTILEACTOR: Failed to Load Material"));
	}

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = false;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.6f;
}

// Called when the game starts or when spawned
void ACMProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACMProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACMProjectileActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
}

