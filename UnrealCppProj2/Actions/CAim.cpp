#include "CAim.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "CHUD.h"
#include "Components/CStateComponent.h"


UCAim::UCAim()
{
	CHelpers::GetAsset<UCurveFloat>(&Curve, "CurveFloat'/Game/Actions/C_Aim.C_Aim'");
}

void UCAim::BeginPlay(ACharacter* InCharacter)
{
	OwnerCharacter = InCharacter;
	SpringArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	Camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);

	Hud = OwnerCharacter->GetWorld()->GetFirstPlayerController()->GetHUD<ACHUD>();
	CLog
#if 0
	TimelineFloat.BindUFunction(this, "Zooming");
	Timeline.AddInterpFloat(Curve, TimelineFloat);

	Timeline.SetPlayRate(200);
#endif
}

void UCAim::OnAim()
{
	//CLog::Print("OnAim");
	bInZoom = true;
	Hud->SetDraw();

	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SocketOffset = FVector(0, 50, 10);	
	//SpringArm->bEnableCameraLag = false;
	//OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	Camera->FieldOfView = 30;
	//Timeline.PlayFromStart();
}

void UCAim::OffAim()
{
	//CLog::Print("OffAim");
	CheckFalse(IsAvailable());
	CheckFalse (bInZoom);

	bInZoom = false;
	Hud->SetNotDraw();

	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SocketOffset = FVector(0, 0, 10);	
	//SpringArm->bEnableCameraLag = true;
	//OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;

	Camera->FieldOfView = 90;

	//Timeline.ReverseFromEnd();
}

void UCAim::Tick(float DeltaTime)
{
	//Timeline.TickTimeline(DeltaTime);
}

void UCAim::Zooming(float Value)
{
	Camera->FieldOfView = Value;
}
