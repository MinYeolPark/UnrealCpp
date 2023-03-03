#include "Widgets/CUserWidget_Main.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "CPlayerController.h"
#include "CUserWidget_Main.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "CUserWidget_HUD.h"

void UCUserWidget_Main::NativeConstruct()
{
	Super::NativeConstruct();
	EnterButton = Cast<UButton>(GetWidgetFromName(TEXT("btnEnter")));
	CheckNull(EnterButton);
	CLog::Log("Add button delegate");
	EnterButton->OnClicked.AddDynamic(this, &UCUserWidget_Main::OnEnterButton);

}

void UCUserWidget_Main::OnEnterButton()
{
	TextField = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("txtField")));
	CheckNull(TextField);
	CLog::Log(TextField->GetText().ToString());

	auto PlayerController = Cast<ACPlayerController>(GetOwningPlayer());
	CheckNull(PlayerController);
	PlayerController->ChangeToHUDWidget();
	PlayerController->SetInputMode(FInputModeGameOnly());	
	PlayerController->bShowMouseCursor = false;
#if 0
	PlayerController->GetHUDWidget()->UpdatePlayerName(TextField->GetText());
#endif
	CLog::Log("On Enter");
}

void UCUserWidget_Main::SetName(FName NewName)
{

}
