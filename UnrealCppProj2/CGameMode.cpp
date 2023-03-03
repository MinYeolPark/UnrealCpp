#include "CGameMode.h"
#include "Global.h"
#include "CPlayerController.h"
#include "CPlayerState.h"

ACGameMode::ACGameMode()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, 
		"Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");

	//CHelpers::GetClass<AHUD>(&HUDClass,
	//	"Blueprint'/Game/BP_CHUD.BP_CHUD_C'");

	PlayerControllerClass = ACPlayerController::StaticClass();
	PlayerStateClass = ACPlayerState::StaticClass();
}

void ACGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	auto PlayerState = Cast<ACPlayerState>(NewPlayer->PlayerState);
	PlayerState->InitPlayerData();
}
