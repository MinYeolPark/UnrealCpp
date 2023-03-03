#include "CEnemy.h"
#include "Global.h"
#include "Actions/CActionData.h"
#include "AI/CEnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CActionComponent.h"
#include "Components/CapsuleComponent.h"

#include "Components/WidgetComponent.h"
#include "Widgets/CUserWidget_Health.h"
#include "Widgets/CUserWidget_Name.h"

#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	CHelpers::CreateComponent<UWidgetComponent>(this, &NameWidget, "NameWidget", GetMesh());
	CHelpers::CreateComponent<UWidgetComponent>(this, &HealthWidget, "HealthWidget", GetMesh());

	CHelpers::CreateActorComponent<UCStatusComponent>(this, &Status, "Status");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UCMontagesComponent>(this, &Montages, "Montages");
	CHelpers::CreateActorComponent<UCActionComponent>(this, &Action, "Action");

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);

	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/Enemy/ABP_CEnemy.ABP_CEnemy_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;

	TSubclassOf<UCUserWidget_Name> nameClass;
	CHelpers::GetClass<UCUserWidget_Name>(&nameClass, "WidgetBlueprint'/Game/Widgets/WB_Name2.WB_Name2_C'");

	NameWidget->SetWidgetClass(nameClass);
	NameWidget->SetRelativeLocation(FVector(0, 0, 240));
	NameWidget->SetDrawSize(FVector2D(240, 30));
	NameWidget->SetWidgetSpace(EWidgetSpace::Screen);

	TSubclassOf<UCUserWidget_Health> healthClass;
	CHelpers::GetClass<UCUserWidget_Health>(&healthClass, "WidgetBlueprint'/Game/Widgets/WB_Health2.WB_Health2_C'");

	HealthWidget->SetWidgetClass(healthClass);
	HealthWidget->SetRelativeLocation(FVector(0, 0, 190));
	HealthWidget->SetDrawSize(FVector2D(120, 20));
	HealthWidget->SetWidgetSpace(EWidgetSpace::Screen);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	AIControllerClass = ACEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	IsAttacking = false;
}

void ACEnemy::BeginPlay()
{
	UMaterialInstanceConstant* body;
	UMaterialInstanceConstant* logo;

	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&body, "MaterialInstanceConstant'/Game/Materials/M_UE4Man_Body_Inst.M_UE4Man_Body_Inst'");
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&logo, "MaterialInstanceConstant'/Game/Materials/M_UE4Man_ChestLogo_Inst.M_UE4Man_ChestLogo_Inst'");

	BodyMaterial = UMaterialInstanceDynamic::Create(body, this);
	LogoMaterial = UMaterialInstanceDynamic::Create(logo, this);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	Super::BeginPlay();

	State->OnStateTypeChanged.AddDynamic(this, &ACEnemy::OnStateTypeChanged);
	
	NameWidget->InitWidget();
	Cast<UCUserWidget_Name>(NameWidget->GetUserWidgetObject())->SetNameText(GetActorLabel());

	HealthWidget->InitWidget();
	Cast<UCUserWidget_Health>(HealthWidget->GetUserWidgetObject())->Update(Status->GetHealth(),
		Status->GetMaxHealth());

	Action->SetUnarmedMode();

	Action->SetIceBallMode();
}


void ACEnemy::ChangeColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	DamageInstigator = EventInstigator;
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	State->SetHittedMode();

	return Status->GetHealth();
}

void ACEnemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNextType)
{
	switch (InNextType)
	{
		case EStateType::Hitted:
			Hitted();
			break;

		case EStateType::Dead:
			Dead();
			break;
	}
}

void ACEnemy::RestoreColor()
{
	CheckNull(Action->GetCurrent());
	FLinearColor color = Action->GetCurrent()->GetEquipmentColor();	
	ChangeColor(color);
}

void ACEnemy::Hitted()
{
	Status->SubHealth(DamageValue);

	Cast<UCUserWidget_Health>(HealthWidget->GetUserWidgetObject())->Update(
		Status->GetHealth(),
		Status->GetMaxHealth()
	);

	DamageValue = 0.0f;

	Status->SetStop();

	if(Status->GetHealth() <= 0.0f)
	{
		State->SetDeadMode();
		return;
	}

	Montages->PlayHitted();

	FVector start = GetActorLocation();
	FVector target = DamageInstigator->GetPawn()->GetActorLocation();

	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, target));
	DamageInstigator = NULL;

	FVector direction = target - start;
	direction.Normalize();

	LaunchCharacter(-direction * LaunchAmount, true, false);

	ChangeColor(FLinearColor(1, 0, 0, 1));
	UKismetSystemLibrary::K2_SetTimer(this, "RestoreColor", 0.1f, false);
}

void ACEnemy::Dead()
{
	CheckFalse(State->IsDeadMode());
	Montages->PlayDead();
}

void ACEnemy::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("ENEMY ATTACK"));
	Montages->PlayThrow();
}

void ACEnemy::OnAttackEnded(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Warning, TEXT("ENEMY ATTACKEnd"));
	CLog::Log(IsAttacking);

	if (OnAttackEnd.IsBound())
		OnAttackEnd.Broadcast();
}

void ACEnemy::Begin_Dead()
{
	Action->OffAllCollision();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACEnemy::End_Dead()
{
	Destroy();
}
