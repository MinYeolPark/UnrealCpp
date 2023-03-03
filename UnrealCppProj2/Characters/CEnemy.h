#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/ICharacter.h"
#include "Components/CStateComponent.h"
#include "CEnemy.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
UCLASS()
class UNREALCPPPROJ2_API ACEnemy : public ACharacter, public IICharacter
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;
	
private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

public:
	virtual void ChangeColor(FLinearColor InColor) override;

	virtual float TakeDamage(float Damage, FDamageEvent const& FDamageEvent, 
		AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(EditAnywhere, Category = "Hitted")
		float LaunchAmount = 100.0f;

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* Action;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* NameWidget;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* HealthWidget;

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNextType);

	UFUNCTION()
		void RestoreColor();

private:
	class AController* DamageInstigator;
	float DamageValue;

private:

	void Hitted();
	void Dead();
public:
	virtual void Begin_Dead() override;
	virtual void End_Dead() override;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	void Attack();
	void OnAttackEnded(UAnimMontage* Montage, bool bInterrupted);
	FOnAttackEndDelegate OnAttackEnd;

	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere, Category = "UI")
		FName EnemyName;

	FName GetEnemyName() { return EnemyName; }
};
