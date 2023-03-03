#include "CPlayerController.h"
#include "Global.h"
#include "Widgets/CUserWidget_HUD.h"
#include "Widgets/CUserWidget_Main.h"
ACPlayerController::ACPlayerController()
{
	CHelpers::GetClass<UCUserWidget_HUD>(&HUDWidgetClass, "/Game/Widgets/UI_HUD.UI_HUD_C");
#if 1
	//CHelpers::GetClass<UCUserWidget_Main>(&MainWidgetClass, "/Game/Widgets/WB_Main.WB_Main_C");	
	static ConstructorHelpers::FClassFinder<UCUserWidget_Main> UI_NAME(TEXT("/Game/Widgets/WB_Main.WB_Main_C"));
	if (UI_NAME.Succeeded())
	{
		MainWidgetClass = UI_NAME.Class;
	}
#endif
}

void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//SetInputMode(FInputModeGameAndUI());
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	ChangeMenuWidget(MainWidgetClass);
}

void ACPlayerController::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
#if 1
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass);
		if(CurrentWidget!=nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
#endif
}

void ACPlayerController::ChangeToHUDWidget()
{
	ChangeMenuWidget(HUDWidgetClass);
}

