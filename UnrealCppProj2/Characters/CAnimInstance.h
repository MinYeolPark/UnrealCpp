#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/CActionComponent.h"
#include "CAnimInstance.generated.h"

UCLASS()
class UNREALCPPPROJ2_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EActionType ActionType;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
		void OnActionTypeChanged(EActionType InPrevType, EActionType InNewType);

};
