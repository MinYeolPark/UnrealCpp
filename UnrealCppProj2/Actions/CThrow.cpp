#include "CThrow.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACThrow::ACThrow()
{
	CHelpers::CreateComponent<USphereComponent>(this, &Sphere, "Sphere");
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Particle, "Particle", Sphere);
	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &ProjectileMoveComp, "Projectile");

	RootComponent = Sphere;

	//Sphere->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	//Sphere->CanCharacterStepUpOn = ECB_No;
	Sphere->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	ProjectileMoveComp->InitialSpeed = 4000.0f;
	ProjectileMoveComp->MaxSpeed = 8000.0f;
	ProjectileMoveComp->ProjectileGravityScale = 0.0f;
	ProjectileMoveComp->bRotationFollowsVelocity = true;

	InitialLifeSpan = 3.0f;
}

void ACThrow::BeginPlay()
{
	Super::BeginPlay();

	TArray<USphereComponent*> components;
	GetComponents<USphereComponent>(components);

	for(UShapeComponent* component : components)
	{
		component->OnComponentBeginOverlap.AddDynamic(this, &ACThrow::OnComponentBeginOverlap);
	}
}

void ACThrow::InitVelocity(const FVector& ShootDirection)
{
	ProjectileMoveComp->Velocity = ShootDirection * ProjectileMoveComp->InitialSpeed;
}

void ACThrow::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMoveComp->Velocity = ShootDirection * ProjectileMoveComp->InitialSpeed;
}

void ACThrow::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!!Explosion)
	{
		FTransform transform = ExplosionTransform;
		transform.AddToTranslation(SweepResult.Location);
		transform.SetRotation(FQuat(SweepResult.ImpactNormal.Rotation()));

		OtherComponent->AddImpulseAtLocation(GetVelocity() * 100.0f, SweepResult.ImpactPoint);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, transform);
	}

	if (OnThrowBeginOverlap.IsBound())
		OnThrowBeginOverlap.Broadcast(SweepResult);

	Destroy();
}