#pragma once

#include "AIController.h"
#include "CEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPPPROJ2_API ACEnemyAIController : public AAIController
{
	GENERATED_BODY()

	ACEnemyAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
public:
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;
	UPROPERTY()
		class UBlackboardData* BBAsset;
};
