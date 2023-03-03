#include "Widgets/CUserWidget_HUD.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "CPlayerController.h"

//void UCUserWidget_HUD::BindCharacterStat(UABCharacterStatComponent* CharacterStat)
//{
//	CheckNull(nullptr != CharacterStat);
//	//CurrentCharacterStat = CharacterStat;
//	//CharacterStat->OnHPChanged.AddUObject(this, &UABHUDWidget::UpdateCharacterStat);
//	//UpdateCharacterStat();
//}

void UCUserWidget_HUD::BindPlayerState(ACPlayerState* PlayerState)
{
	CheckNull(nullptr != PlayerState);
}

void UCUserWidget_HUD::NativeConstruct()
{
	Super::NativeConstruct();
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
	CheckNull(nullptr != HPBar);

	ExpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbExp")));
	CheckNull(nullptr != ExpBar);

	PlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtPlayerName")));
	CheckNull(nullptr != PlayerName);

	PlayerLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtLevel")));
	CheckNull(nullptr != PlayerLevel);

	CurrentScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentScore")));
	CheckNull(nullptr != CurrentScore);

	HighScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtHighScore")));
	CheckNull(nullptr != HighScore);
}

void UCUserWidget_HUD::UpdateCharacterStat()
{

}

void UCUserWidget_HUD::UpdatePlayerState()
{

}

void UCUserWidget_HUD::UpdatePlayerName(FText NewName)
{
	CheckNull(PlayerName);
	PlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtPlayterName")));

	CLog::Log(PlayerName->GetText().ToString());
	//PlayerName->SetText(NewName);
	CLog::Log("Player Name change");
}
