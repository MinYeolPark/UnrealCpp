#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

UCLASS()
class UNREALCPPPROJ2_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()
				
		
public:
	ACPlayerController();


	virtual void BeginPlay() override;

	void ChangeToHUDWidget();
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HUD)
		TSubclassOf<class UCUserWidget_HUD> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
		TSubclassOf<class UCUserWidget_Main> MainWidgetClass;
private:
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UPROPERTY()
		class UCUserWidget_HUD* HUDWidget;
	UPROPERTY()
		class UCUserWidget_Main* MainWidget;
	UPROPERTY()
		UUserWidget* CurrentWidget;

public:
	FORCEINLINE TSubclassOf<class UCUserWidget_HUD> GetHudWidgetClass() { return HUDWidgetClass; }
	FORCEINLINE UCUserWidget_Main* GetMainMenuWidget() { return MainWidget; }
	FORCEINLINE UCUserWidget_HUD* GetHUDWidget() { return HUDWidget; }
};
