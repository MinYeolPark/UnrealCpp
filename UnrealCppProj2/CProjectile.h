#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProjectile.generated.h"

UCLASS()
class UNREALCPPPROJ2_API ACProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ACProjectile();

	UPROPERTY(EditDefaultsOnly, Category = State)
		float InitialSpeed;
	UPROPERTY(EditDefaultsOnly, Category = State)
		float MaxSpeed;
	UPROPERTY(EditDefaultsOnly, Category = State)
		FName ProjectileName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		class USphereComponent* CollisionComp;

	UPROPERTY(EditDefaultsOnly, Category = Particle)
		class UParticleSystemComponent* Particle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		class UProjectileMovementComponent* ProjectileMoveComp;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFormSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FORCEINLINE class USphereComponent* GetProjectileCollision() const { return CollisionComp; }
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMoveComp; }

};
