#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_FireStorm.generated.h"

UCLASS()
class UNREALCPPPROJ2_API ACDoAction_FireStorm : public ACDoAction
{
	GENERATED_BODY()

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

private:
	class UBoxComponent* Box;
	class UParticleSystemComponent* Attached;

private:
	float Angle;

	TArray<class ACharacter*> HittedCharacter;

private:
	UPROPERTY(EditAnywhere)
		float Time = 5.0f;

	UPROPERTY(EditAnywhere)
		float Distance = 200.0f;

	UPROPERTY(EditAnywhere)
		float Speed = 100.0f;

	UPROPERTY(EditAnywhere)
		float HittedTime = 0.25f;

private:
	UFUNCTION()
		void Finish();

	UFUNCTION()
		void Hitted();

	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker,
		class AActor* InAttackCauser,
		class ACharacter* InOtherCharacter) override;
	
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker,
		class AActor* InAttackCauser,
		class ACharacter* InOtherCharacter) override;
};
