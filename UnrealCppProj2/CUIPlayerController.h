#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CUIPlayerController.generated.h"

UCLASS()
class UNREALCPPPROJ2_API ACUIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	ACUIPlayerController();
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UUserWidget> UIWidgetClass;

	UPROPERTY()
		class UUserWidget* UIWidgetInstance;
};
