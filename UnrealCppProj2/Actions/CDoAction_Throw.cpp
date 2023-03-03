#include "CDoAction_Throw.h"

#include "CThrow.h"
#include "Global.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Actions/CAim.h"

void ACDoAction_Throw::BeginPlay()
{
	Super::BeginPlay();
	GLog->Log(TEXT("Thorw Init"));
	Aim = NewObject<UCAim>();
	Aim->BeginPlay(OwnerCharacter);
	//Aim->ConditionalFinishDestroy();
}

void ACDoAction_Throw::DoAction()
{
	Super::DoAction();

	if (Aim->IsAvailable())
		CheckFalse(Aim->InZoom());

	CheckFalse(State->IsIdleMode());
	State->SetActionMode();
	
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage,
		Datas[0].PlayRatio,
		Datas[0].StartSection);	
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Throw::Begin_DoAction()
{
#if 0
	FVector location = OwnerCharacter->GetMesh()->GetSocketLocation(
		"Hand_Throw_Projectile");
	FRotator rotator = OwnerCharacter->GetController()->GetControlRotation();

	FTransform transform = Datas[0].EffectTransform;
	transform.AddToTranslation(location);
	transform.SetRotation(FQuat(rotator));

	FActorSpawnParameters param;
	param.Owner = OwnerCharacter;

	GLog->Log(TEXT("Thorw Action"));
		
	ACThrow* throwObject = OwnerCharacter->GetWorld()->SpawnActorDeferred<ACThrow>(
		Datas[0].ThrowClass, transform, OwnerCharacter, NULL,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
#elif 0
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	FTransform ProjectileSpawnTransform = OwnerCharacter->GetMesh()->GetSocketTransform("Hand_Throw_Projectile");
	ProjectileSpawnTransform.SetLocation(ProjectileSpawnTransform.GetLocation());
	ACThrow* throwObject = OwnerCharacter->GetWorld()->SpawnActor<ACThrow>(Datas[0].ThrowClass, ProjectileSpawnTransform, SpawnParams);
	if (throwObject)
	{		
		throwObject->FireInDirection(OwnerCharacter->GetActorForwardVector());
	}
#elif 1
	FVector location = OwnerCharacter->GetMesh()->GetSocketLocation(
		"Hand_Throw_Projectile");
	location.X -= 180;
	FRotator rotator = OwnerCharacter->GetController()->GetControlRotation();
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	ACThrow* throwObject = OwnerCharacter->GetWorld()->SpawnActor<ACThrow>(Datas[0].ThrowClass, location, rotator, ActorSpawnParams);
	throwObject->OnThrowBeginOverlap.AddDynamic(this, &ACDoAction_Throw::OnThrowBeginOverlap);
	UGameplayStatics::FinishSpawningActor(throwObject, Datas[0].EffectTransform);
#endif
}

void ACDoAction_Throw::End_DoAction()
{
	State->SetIdleMode();
	Status->SetMove();
}

void ACDoAction_Throw::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Aim->Tick(DeltaSeconds);
}

void ACDoAction_Throw::OnAim()
{
	Aim->OnAim();
}

void ACDoAction_Throw::OffAim()
{
	Aim->OffAim();
}

void ACDoAction_Throw::OnThrowBeginOverlap(FHitResult InHitResult)
{
	CLog::Log(InHitResult.GetActor()->GetName());

	FDamageEvent e;
	InHitResult.GetActor()->TakeDamage(Datas[0].Power, e, OwnerCharacter->GetController(), this);	
}
