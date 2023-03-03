#pragma once

#include "CoreMinimal.h"
#include "Components/CStateComponent.h"
#include "GameFramework/Character.h"
#include "Characters/ICharacter.h"
#include "CPlayer.generated.h"

UCLASS()
class UNREALCPPPROJ2_API ACPlayer : public ACharacter, public IICharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* Action;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
		class UCTargetComponent* Target;

	UPROPERTY(VisibleDefaultsOnly)
		TSubclassOf<class UCUserWidget_ActionList> ActionListClass;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* NameWidget;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* HealthWidget;
private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);

	void OnAvoid();

	void Begin_Roll();
	void Begin_Backstep();

public:
	void SetPlayerName(FText NewName);
	
	void End_Roll();
	void End_Backstep();

private:
	void OnFist();
	void OnOneHand();
	void OnTwoHand();
	void OnWarp();
	void OnFireStorm();
	void OnIceBall();
	void OnTarget();
	void OnTargetLeft();
	void OnTargetRight();
	void OnDoAction();
	void OnAim();
	void OffAim();
	void OnViewActionList();
	void OffViewActionList();

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;
	class UCUserWidget_ActionList* ActionList;

public:
	virtual void ChangeColor(FLinearColor InColor) override;

public:
	FORCEINLINE class UCUserWidget_ActionList* GetActionList() { return ActionList; }
	
};
