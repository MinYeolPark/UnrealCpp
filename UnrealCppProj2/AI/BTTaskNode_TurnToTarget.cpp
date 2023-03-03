#include "AI/BTTaskNode_TurnToTarget.h"
#include "CEnemyAIController.h"
#include "Characters/CEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_TurnToTarget::UBTTaskNode_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTaskNode_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Character = Cast<ACEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Character)
		return EBTNodeResult::Failed;
	 
	auto Target = Cast<ACEnemy>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ACEnemyAIController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - Character->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	UE_LOG(LogTemp, Warning, TEXT("Turn to target Task"));

	Character->SetActorRotation(FMath::RInterpTo(Character->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}