#include "CEnemyAIController.h"
#include "Global.h"
#include "Characters/CEnemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


const FName ACEnemyAIController::HomePosKey(TEXT("HomePos"));
const FName ACEnemyAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ACEnemyAIController::TargetKey(TEXT("Target"));
ACEnemyAIController::ACEnemyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/BB_CEnemy.BB_CEnemy"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/BT_CEnemy.BT_CEnemy"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

}

void ACEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, (UBlackboardComponent*)Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Warning, TEXT("AI Error"));
		}		
	}	
}

void ACEnemyAIController::OnUnPossess()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr != BehaviorTreeComponent)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}
