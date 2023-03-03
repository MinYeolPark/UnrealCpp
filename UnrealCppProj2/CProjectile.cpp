#include "CProjectile.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Characters/CEnemy.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
// Sets default values
ACProjectile::ACProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USphereComponent>(this, &CollisionComp, "Sphere");
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Particle, "Particle", CollisionComp);
	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &ProjectileMoveComp, "Projectile");

	RootComponent = CollisionComp;
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACProjectile::OnOverlapBegin);
	InitialLifeSpan = 3.0f;

	ProjectileMoveComp->InitialSpeed = 4000.0f;
	ProjectileMoveComp->MaxSpeed = 8000.0f;
	ProjectileMoveComp->ProjectileGravityScale = 0.0f;
	ProjectileMoveComp->bRotationFollowsVelocity = true;
	ProjectileMoveComp->bShouldBounce = true;
}

void ACProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFormSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->IsA(ACPlayer::StaticClass()))
		{
			Destroy();
		}
	}
}

void ACProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}
