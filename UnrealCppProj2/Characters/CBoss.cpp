#include "Characters/CBoss.h"
#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CActionComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACBoss::ACBoss()
{

	GetMesh()->SetRelativeLocation(FVector(0, 0, -120));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

}

void ACBoss::BeginPlay()
{
	Super::BeginPlay();

	Action->SetFireStormMode();
	GetCapsuleComponent()->SetCapsuleRadius(44.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(122.0f);

	GetCharacterMovement()->MaxWalkSpeed = 180.0f;	

	Attack();
}
