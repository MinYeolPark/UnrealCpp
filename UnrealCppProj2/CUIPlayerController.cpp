#include "CUIPlayerController.h"
#include "Global.h"
#include "Blueprint/UserWidget.h"
ACUIPlayerController::ACUIPlayerController()
{
	CHelpers::GetClass<UUserWidget>(&UIWidgetClass, "/Game/Widgets/WB_Title.WB_Title_C");
}

void ACUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CheckNull(UIWidgetClass);

	UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
	CheckNull(UIWidgetInstance);

	UIWidgetInstance->AddToViewport();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;
}
