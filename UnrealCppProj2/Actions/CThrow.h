#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CThrow.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FThrowBeginOverlap, FHitResult, InHitResult);

UCLASS()
class UNREALCPPPROJ2_API ACThrow : public AActor
{
	GENERATED_BODY()
	
public:	
	ACThrow();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* Explosion;

	UPROPERTY(EditDefaultsOnly)
		FTransform ExplosionTransform;

	UPROPERTY(EditDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* Particle;

	UPROPERTY(EditDefaultsOnly)
		class UProjectileMovementComponent* ProjectileMoveComp;


public:
	UPROPERTY(BlueprintAssignable)
		FThrowBeginOverlap OnThrowBeginOverlap;	

public:
	void InitVelocity(const FVector& ShootDirection);
	void FireInDirection(const FVector& ShootDirection);

private:
	UFUNCTION()
		void OnComponentBeginOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
};
